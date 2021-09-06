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


#define NETISN4_BUTTONS_POLL_INTERVAL		100
#define NETISN4_BUTTONS_DEBOUNCE_INTERVAL	(3 * NETISN4_BUTTONS_POLL_INTERVAL)
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);

#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_C3
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_C1
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_B7
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_B7

static struct gpio_led netisn4_leds_gpio[] __initdata = {
	{
		.name		= "rtl819x:yellow:sys",
		.gpio		= BSP_WPS_LED_PIN,
		.active_low	= 1,
	}
};

static struct gpio_keys_button netisn4_buttons[] __initdata = {
#if 0
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = NETISN4_BUTTONS_DEBOUNCE_INTERVAL,
		.gpio		= BSP_RESET_BTN_PIN,		
		.active_low	= 1,
	}
	,
 	{
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = NETISN4_BUTTONS_DEBOUNCE_INTERVAL,
		.gpio		= BSP_WPS_BTN_PIN,
		.active_low	= 1,
	}
#endif
};

struct gpio netisn4_phy_reset_pin_data = {
	.gpio		= BSP_GPIO_PIN_H2,
	.flags          = GPIOF_ACTIVE_LOW,
	.label		= "GPIO_H2",
};

static struct platform_device __initdata *netisn4_devs[] = {
	&rtl819x_phy_reset_pin,
};

#define SET_PINMUX(reg, field, val)\
	REG32(reg) = (REG32(reg) & (~(0xF << field))) | (val << field)



static void __init netisn4_setup(void)
{
	int i;


	rtl819x_phy_reset_pin.dev.platform_data = &netisn4_phy_reset_pin_data;

	platform_add_devices(netisn4_devs, ARRAY_SIZE(netisn4_devs));
	
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(netisn4_leds_gpio),
		netisn4_leds_gpio);

	for (i=0; i<ARRAY_SIZE(netisn4_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(netisn4_leds_gpio[i].gpio);
	}

	for (i=0; i<ARRAY_SIZE(netisn4_buttons); i++) {
		rtl819x_gpio_pin_enable(netisn4_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, NETISN4_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(netisn4_buttons),
				       netisn4_buttons);

//	netisn4_set_sd_pinmux();
}

MIPS_MACHINE(RTL8197_MACH_NETISN4, "NETISN4", " NETIS N4",
			 netisn4_setup);
