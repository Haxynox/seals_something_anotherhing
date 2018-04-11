# Init Resources
PRODUCT_PACKAGES += \
	init.bluetooth.rc \
	android.hardware.bluetooth@1.0-impl \
	libbt-vendor

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
	ro.bt.bdaddr_path="/efs/bluetooth/bt_addr"

# Bluetooth workaround:
# The new CAF code defaults to MCT HAL, but we
# need the old H4 HAL for our Broadcom WiFi.
PRODUCT_PROPERTY_OVERRIDES += \
	qcom.bluetooth.soc=rome
