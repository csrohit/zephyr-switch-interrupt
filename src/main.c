#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree/gpio.h>

#define LED DT_NODELABEL(led)
static struct gpio_dt_spec spec = GPIO_DT_SPEC_GET(LED, gpios);
static struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(button), gpios);

static struct gpio_callback button_cb;

static gpio_callback_handler_t button_pressed(struct device *dev,
                         struct gpio_callback *cb,
                         uint32_t pins)
{
  gpio_pin_toggle_dt(&spec);
}
void main(void)
{
    int ret;
    if (!device_is_ready(button.port))
    {
        return;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0)
    {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, button.port->name, button.pin);
        return;
    }

    if (!device_is_ready(spec.port))
    {
        return;
    }

    ret = gpio_pin_configure_dt(&spec, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return;
    }

    ret = gpio_pin_interrupt_configure_dt(&button,
					      GPIO_INT_EDGE_RISING);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button.port->name, button.pin);
		return;
	}


    gpio_init_callback(&button_cb, button_pressed, BIT(button.pin));

    gpio_add_callback(button.port, &button_cb);




    // while (1)
    // {
    //     ret = gpio_pin_toggle_dt(&spec);
    //     k_msleep(1000);
    // }
}
