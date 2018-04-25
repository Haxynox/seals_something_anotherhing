DEVICE_PATH := device/samsung/hero-common

# Configs
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/gps/gps.xml:system/vendor/etc/gnss/gps.xml \
	$(LOCAL_PATH)/configs/lhd.conf:system/etc/lhd.conf

# HIDL
PRODUCT_PACKAGES += \
	android.hardware.gnss@1.0-impl \
	android.hardware.gnss@1.0-service

PRODUCT_PACKAGES += \
	libsensor_shim

