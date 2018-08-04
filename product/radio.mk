DEVICE_PATH := device/samsung/hero-common

# Copy stock APN config as lineage one seams to be quite broken and outdated
PRODUCT_COPY_FILES += \
	$(DEVICE_PATH)/configs/apns-conf.xml:system/etc/apns-conf.xml \
	$(DEVICE_PATH)/configs/spn-conf.xml:system/etc/spn-conf.xml

# Init Resources
PRODUCT_PACKAGES += \
	init.baseband.rc \
	init.baseband.sh

# Packages
PRODUCT_PACKAGES += \
	libxml2 \
	libprotobuf-cpp-full \
	libsecril-client \
	android.hardware.radio@1.0 \
	android.hardware.radio.deprecated@1.0 \
	modemloader \
	libsecril-client-sap

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
	persist.radio.add_power_save=1 \
	persist.radio.apm_sim_not_pwdn=1 \
	ro.telephony.default_network=9 \
	ro.ril.gprsclass=10 \
	ro.ril.hsxpa=1 \
	persist.data.netmgrd.qos.enable=false \
	ro.use_data_netmgrd=false \
	ro.ril.telephony.mqanelements=6 \
	telephony.lteOnGsmDevice=1 \
	telephony.lteOnCdmaDevice=0 \
	ro.telephony.get_imsi_from_sim=true \
	ro.ril.force_eri_from_xml=true \
	net.tethering.noprovisioning=true \
	ro.debug_level=0x494d \
	rild.libpath=/system/lib64/libsec-ril.so \
	rild.libargs=-d /dev/umts_ipc0 \
	vendor.sec.rild.libpath=/vendor/lib64/libsec-ril.so \
	vendor.sec.rild.libpath2=/vendor/lib64/libsec-ril-dsds.so
