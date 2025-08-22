/*
 * Copyright (c) 2024 Pete Johanson
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <soc.h>
#include <zephyr/init.h>
#include <zephyr/retention/retention.h>
#include <zephyr/retention/bootmode.h>
#include <pico/bootrom.h>

static FUNC_NORETURN void jump_to_bootloader(void)
{
	uint32_t boot_led_mask = 0;

#if DT_HAS_CHOSEN(zephyr_rpi_pico_boot_led)
	boot_led_mask = BIT(DT_GPIO_PIN_BY_IDX(DT_CHOSEN(zephyr_rpi_pico_boot_led), gpios, 0));
#endif

	reset_usb_boot(boot_led_mask,0);

	while (1) { }
}

static int rp2_bootloader_check_boot_init(void)
{
	if (bootmode_check(BOOT_MODE_TYPE_BOOTLOADER) > 0) {
		bootmode_clear();
		jump_to_bootloader();
	}

	return 0;
}

SYS_INIT(rp2_bootloader_check_boot_init, PRE_KERNEL_2, 0);

