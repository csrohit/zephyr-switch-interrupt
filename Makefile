BUILD_DIR:= bin
OPEN_OCD_HOME:=/usr/local/bin/openocd

all: source build

source:
	cmake -B${BUILD_DIR}

build:
	${MAKE} -C ${BUILD_DIR} -j11

flash:
	openocd -d2 -s ${OPEN_OCD_HOME}/scripts -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32f1x.cfg -c "program {./${BUILD_DIR}/zephyr/zephyr.elf}  verify reset; shutdown;"

clean:
	@echo 'Cleaning build'
	rm -rf ${BUILD_DIR}

.phony: flash clean