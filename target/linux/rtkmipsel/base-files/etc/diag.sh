#!/bin/sh
# Copyright (C) 2009-2018 OpenWrt.org

. /lib/functions.sh
. /lib/functions/leds.sh

get_status_led() {
	local board=$(board_name)

	case $board in
	kinkan)
		status_led="kinkan:green:status"
		;;
	komikan)
		status_led="komikan:green:led0"
		;;
	ac10u)
		status_led="ac10u:green:led0"
		;;
	a3002ru)
		status_led="a3002ru:yellow:led0"
		;;
	esac
}

set_state() {
	get_status_led

	case "$1" in
	preinit)
		status_led_blink_preinit
		;;
	failsafe)
		status_led_blink_failsafe
		;;
	preinit_regular)
		status_led_blink_preinit_regular
		;;
	done)
		status_led_on
		;;
	esac
}
