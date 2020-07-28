 /*
 *  8devices Komikan devboard support
 *
 *  Copyright (C) 2018 Mantas Pucka <mantas@8devices.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/leds.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <generated/autoconf.h>

#include "gpio.h"
#include "bspchip.h"
#include "machtypes.h"
#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"


#define A3002RU_BUTTONS_POLL_INTERVAL		100
#define A3002RU_BUTTONS_DEBOUNCE_INTERVAL	(3 * A3002RU_BUTTONS_POLL_INTERVAL)
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);

#if defined(CONFIG_RTL_8367R_SUPPORT)
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_G6
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_H0
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_H1
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_H1
#define BSP_8367R_RST_PIN		BSP_GPIO_PIN_H2
#define BSP_8367R_I2C_PIN1		BSP_GPIO_PIN_C2
#define BSP_8367R_I2C_PIN2		BSP_GPIO_PIN_C3
#else
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_C3
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_C1
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_B7
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_B7
#endif

static struct gpio_led a3002ru_leds_gpio[] __initdata = {
	{
		.name		= "rtl819x:green:sys",
		.gpio		= BSP_WPS_LED_PIN,
		.active_low	= 1,
	}
};

static struct gpio_keys_button a3002ru_buttons[] __initdata = {
#if 0
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = A3002RU_BUTTONS_DEBOUNCE_INTERVAL,
		.gpio		= BSP_RESET_BTN_PIN,		
		.active_low	= 1,
	}
	,
 	{
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = A3002RU_BUTTONS_DEBOUNCE_INTERVAL,
		.gpio		= BSP_WPS_BTN_PIN,
		.active_low	= 1,
	}
#endif
};

struct gpio a3002ru_phy_reset_pin_data = {
	.gpio		= BSP_GPIO_PIN_H2,
	.flags          = GPIOF_ACTIVE_LOW,
	.label		= "GPIO_H2",
};

static struct platform_device __initdata *a3002ru_devs[] = {
	&rtl819x_phy_reset_pin,
};

#define SET_PINMUX(reg, field, val)\
	REG32(reg) = (REG32(reg) & (~(0xF << field))) | (val << field)



static void __init a3002ru_setup(void)
{
	int i;


	rtl819x_phy_reset_pin.dev.platform_data = &a3002ru_phy_reset_pin_data;

	platform_add_devices(a3002ru_devs, ARRAY_SIZE(a3002ru_devs));
	
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(a3002ru_leds_gpio),
		a3002ru_leds_gpio);

	for (i=0; i<ARRAY_SIZE(a3002ru_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(a3002ru_leds_gpio[i].gpio);
	}

	for (i=0; i<ARRAY_SIZE(a3002ru_buttons); i++) {
		rtl819x_gpio_pin_enable(a3002ru_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, A3002RU_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(a3002ru_buttons),
				       a3002ru_buttons);

//	a3002ru_set_sd_pinmux();
}

MIPS_MACHINE(RTL8197_MACH_A3002RU, "A3002RU", "TOTOLINK A3002RU",
			 a3002rusetup);
