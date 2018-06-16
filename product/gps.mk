DEVICE_PATH := device/samsung/hero-common

# HIDL
PRODUCT_PACKAGES += \
	android.hardware.gnss@1.0-impl \
	android.hardware.gnss@1.0-service \
	libsensor_shim

PRODUCT_PACKAGES += \
	android.hidl.base@1.0 \
	android.hidl.manager@1.0

# Config
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/gps/gps.conf:system/etc/gps.conf \
	$(LOCAL_PATH)/configs/lhd.conf:system/etc/lhd.conf
