/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>

#define UART5_DEVICE_NODE DT_NODELABEL(uart5)

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)


/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct device *uart_device = DEVICE_DT_GET(UART5_DEVICE_NODE);

void print_uart(char *msg) {
    for (int i = 0; i < strlen(msg); ++i)
        uart_poll_out(uart_device, msg[i]);
}

void main(void)
{
	int ret;

	if (!device_is_ready(led.port)) {
		return;
	}

        if (!device_is_ready(uart_device)) {
            printf("UART model not found");
        } else  {
            printf("found UART device");
        }

	printf("DEVICE %s READY!", CONFIG_BOARD);

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return;
		}
		printf("Toggling\n");
                print_uart("LGTM!\n");
                k_msleep(SLEEP_TIME_MS);
	}
}
