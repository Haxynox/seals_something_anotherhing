DEVICE_PATH := device/samsung/hero-common

# HIDL
PRODUCT_PACKAGES += \
	android.hardware.gnss@1.0-impl.hero \
	android.hardware.gnss@1.0-service \
	android.hidl.base@1.0 \
	android.hidl.manager@1.0

# Config
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/gps/gps.conf:system/etc/gps_debug.conf \
	$(DEVICE_PATH)/configs/gps/lhd.conf:system/vendor/etc/sensor/lhd.conf \
   	$(DEVICE_PATH)/configs/gps/gps.xml:system/vendor/etc/gnss/gps.xml
