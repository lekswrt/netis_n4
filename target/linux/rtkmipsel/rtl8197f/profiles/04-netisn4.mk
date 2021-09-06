#
# Copyright (C) 2006-2018 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/netisn4
  NAME:=netisn4 Profile
  PRIORITY:=1
#   PACKAGES:= \
# 	  -odhcpd-ipv6only \
# 	  -wpad-mini \
# 	  hostapd-common \
# 	  iw \
# 	  iwinfo \
# 	  kmod-button-hotplug \
# 	  kmod-cfg80211 \
# 	  kmod-fs-vfat \
# 	  kmod-gpio-button-hotplug \
# 	  kmod-input-core \
# 	  kmod-input-evdev \
# 	  kmod-input-gpio-keys \
# 	  kmod-ledtrig-netdev \
# 	  kmod-mac80211 \
# 	  kmod-mmc \
# 	  kmod-rtk-sdmmc \
# 	  kmod-rtl8192cd \
# 	  kmod-scsi-core \
# 	  kmod-usb-core \
# 	  kmod-usb-ehci \
# 	  kmod-usb-ohci \
# 	  kmod-usb-storage \
# 	  kmod-usb2 \
# 	  rpcd \
# 	  rpcd-mod-rrdns \
# 	  rtk_hciattach \
# 	  wireless-regdb \
# 	  wireless-tools \
# 	  wpad \
   
   PACKAGES:= \
 	  -odhcpd-ipv6only \
 	  -wpad-mini \
 	  kmod-rtl8192cd \



endef

define Profile/netisn4/Description
	Default package set compatible with  netis n4
endef
$(eval $(call Profile,netisn4))
