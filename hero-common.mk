#
# Copyright (C) 2017 Fernando Von Arx <fer.vonarx@gmail.com>
# Copyright (C) 2017 Jesse Chan <cjx123@outlook.com>
# Copyright (C) 2017 Ivan Meler <i_ivan@windowslive.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

# Common Overlays
DEVICE_PACKAGE_OVERLAYS += device/samsung/hero-common/overlay

LOCAL_PATH := device/samsung/hero-common

###########################################################
### RAMDISK
###########################################################

PRODUCT_PACKAGES += \
	fstab.samsungexynos8890 \
	init.samsung.rc \
	init.samsungexynos8890.rc \
	ueventd.samsungexynos8890.rc \
	init.samsungexynos8890.usb.rc \
	init.wifi.rc \
	init.gps.rc

###########################################################
### GRAPHICS
###########################################################

# This device is xhdpi.  However the platform doesn't
# currently contain all of the bitmaps at xhdpi density so
# we do this little trick to fall back to the hdpi version
# if the xhdpi doesn't exist.
PRODUCT_AAPT_CONFIG := xlarge
PRODUCT_AAPT_PREF_CONFIG := xxxhdpi
# A list of dpis to select prebuilt apk, in precedence order.
PRODUCT_AAPT_PREBUILT_DPI := xxxhdpi xxhdpi xhdpi hdpi

# Boot animation
TARGET_SCREEN_HEIGHT := 2560
TARGET_SCREEN_WIDTH := 1440

###########################################################
### POWER
###########################################################

PRODUCT_PACKAGES += \
	power.exynos5 \
	android.hardware.power@1.0-impl

###########################################################
### CHARGER
###########################################################

# Offmode charger
# Use LineageOS images if available, aosp ones otherwise
PRODUCT_PACKAGES += \
	charger_res_images \
	lineage_charger_res_images

###########################################################
### PACKAGES
###########################################################

PRODUCT_PACKAGES += \
	libsamsung_symbols \
	SamsungServiceMode \
	Torch \
        HeroDoze \
	thermal.universal8890 \
	android.hidl.base@1.0 \
	android.hidl.manager@1.0 \
	RemovePackages

# Filesystem tools for resizing system partition filesystem
PRODUCT_PACKAGES += \
	e2fsck_static \
	resize2fs_static

# Health
PRODUCT_PACKAGES += \
    android.hardware.health@2.0-impl \
    android.hardware.health@2.0-service

# Trust HAL
PRODUCT_PACKAGES += \
    vendor.lineage.trust@1.0-service

###########################################################
### DTB TOOL
###########################################################

PRODUCT_PACKAGES += \
	dtbhtoolExynos

# Inherit board specific products
-include $(LOCAL_PATH)/product/*.mk

# System properties
-include $(LOCAL_PATH)/system_prop.mk

# call Samsung S.LSI board support package
$(call inherit-product, hardware/samsung_slsi/exynos5/exynos5.mk)
$(call inherit-product, hardware/samsung_slsi/exynos8890/exynos8890.mk)

# call the proprietary setup
$(call inherit-product, vendor/samsung/hero-common/hero-common-vendor.mk)
