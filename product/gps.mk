DEVICE_PATH := device/samsung/hero-common

# HIDL
PRODUCT_PACKAGES += \
	android.hardware.gnss@1.0-impl.hero \
	android.hardware.gnss@1.0-service \

# Shim
PRODUCT_PACKAGES += \
	libsensor_shim

# Config
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/gps/gps.conf:system/etc/gps.conf \
	$(DEVICE_PATH)/configs/gps/lhd.conf:system/etc/lhd.conf \
        $(DEVICE_PATH)/configs/gps/gps.xml:system/etc/gps.xml
