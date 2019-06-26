DEVICE_PATH := device/samsung/hero-common

# Configs
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/nfc/libnfc-sec-hal.conf:system/etc/libnfc-sec-hal.conf \
	$(DEVICE_PATH)/configs/nfc/libnfc-sec.conf:system/etc/libnfc-sec.conf \
	$(DEVICE_PATH)/configs/nfc/nfcee_access.xml:system/etc/nfcee_access.xml \
	$(DEVICE_PATH)/configs/nfc/libnfc-brcm.conf:system/vendor/etc/libnfc-brcm.conf \
	$(DEVICE_PATH)/configs/nfc/libnfc-brcm.conf:system/vendor/etc/libnfc-nci.conf \
	$(DEVICE_PATH)/configs/nfc/libnfc-brcm.conf:system/etc/libnfc-nci.conf

# Packages
PRODUCT_PACKAGES += \
	com.android.nfc_extras \
	Tag \
	NfcNci \
	android.hardware.nfc@1.0-impl

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
        ro.nfc.fw_dl_on_boot=false \
	ro.nfc.port="I2C"
