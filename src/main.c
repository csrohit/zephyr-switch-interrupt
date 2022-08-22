#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree/gpio.h>


static struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET(DT_NODELABEL(green_led), gpios);
static struct gpio_dt_spec led_builtin = GPIO_DT_SPEC_GET(DT_NODELABEL(led_builtin), gpios);
static struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(button1), gpios);

static struct gpio_callback button_cb;
static gpio_callback_handler_t button_pressed(struct device *dev, struct gpio_callback *cb, uint32_t pins);


void main(void)
{
    int ret;

    // check if led is ready
    if (!device_is_ready(led_green.port))
    {
        return;
    }

    // configure led gpio pin as output and set initial value as Logical Active
    ret = gpio_pin_configure_dt(&led_green, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return;
    }

        // check if led is ready
    if (!device_is_ready(led_builtin.port))
    {
        return;
    }

    // configure led gpio pin as output and set initial value as Logical Active
    ret = gpio_pin_configure_dt(&led_builtin, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return;
    }

    // check if the button is ready
    if (!device_is_ready(button.port))
    {
        return;
    }

    // configure button gpio as input
    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0)
    {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, button.port->name, button.pin);
        return;
    }

    // enable interrupt on button for rising edge
    ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_RISING);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button.port->name, button.pin);
		return;
	}

    // initialize callback structure for button interrupt
    gpio_init_callback(&button_cb, button_pressed, BIT(button.pin));

    // attach callback function to button interrupt
    gpio_add_callback(button.port, &button_cb);


    while (1)
    {
        gpio_pin_toggle_dt(&led_builtin);
        k_msleep(1000);
    }
    
}


/**
 * @brief interrupt handler for button pressed rising edge
 * 
 * @param dev pointer to button 
 * @param cb pointer to owner gpio_callback
 * @param pins mask of pins that trigger this interrupt
 * @return gpio_callback_handler_t 
 */
static gpio_callback_handler_t button_pressed(struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
  gpio_pin_toggle_dt(&led_green);
}
