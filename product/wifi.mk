DEVICE_PATH := device/samsung/hero-common

# Configs
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/wifi/p2p_supplicant_overlay.conf:system/etc/wifi/p2p_supplicant_overlay.conf \
	$(DEVICE_PATH)/configs/wifi/wpa_supplicant_overlay.conf:system/etc/wifi/wpa_supplicant_overlay.conf \
	$(LOCAL_PATH)/configs/wifi/filter_ie:system/etc/wifi/filter_ie

# Packages
PRODUCT_PACKAGES += \
	macloader \
	wifiloader \
	hostapd \
	wificond \
	wifilogd \
	wlutil \
	libwpa_client \
	wpa_supplicant \
	wpa_supplicant.conf \
	android.hardware.wifi@1.0-service \
	android.hardware.wifi@1.0 \
	android.hardware.wifi@1.0-impl

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
	wifi.interface=wlan0
