/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <hal/nrf_gpio.h>
#include <nrfx.h>
#include <device.h>
#include <drivers/gpio.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(seeeduino_xiao_ble_board_init);

#define XIAO_BLE_CHARGE_CTRL_PORT DT_LABEL(DT_NODELABEL(gpio0))
#define XIAO_BLE_CHARGE_CTRL_PIN 13

static int setup(const struct device *dev)
{
	ARG_UNUSED(dev);

	const struct device *gpio;
	int err;

	gpio = device_get_binding(XIAO_BLE_CHARGE_CTRL_PORT);
        if (!gpio) {
                LOG_ERR("Could not bind device \"%s\"", XIAO_BLE_CHARGE_CTRL_PORT);
                return -ENODEV;
        }

	err = gpio_pin_configure(gpio, XIAO_BLE_CHARGE_CTRL_PIN, GPIO_OUTPUT_LOW);

	if (err < 0) {
                LOG_ERR("Failed to set charge pin low for high charge rate");
                return err;
	}

	return 0;
}

SYS_INIT(setup, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
