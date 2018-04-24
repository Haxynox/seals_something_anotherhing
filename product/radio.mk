DEVICE_PATH := device/samsung/hero-common

# Copy stock APN config as lineage one seams to be quite broken and outdated
PRODUCT_COPY_FILES += $(DEVICE_PATH)/configs/apns-conf.xml:system/etc/apns-conf.xml

# Init Resources
PRODUCT_PACKAGES += \
	init.baseband.rc \
	init.baseband.sh \
	init.rilchip.rc \
	init.rilcommon.rc

# Packages
PRODUCT_PACKAGES += \
	libxml2 \
	libprotobuf-cpp-full \
	libsecril-client \
	android.hardware.radio@1.0 \
	android.hardware.radio.deprecated@1.0 \
	modemloader \
	rild \
	libreference-ril \
	libsecril-client-sap \
	libril 

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
	persist.radio.add_power_save=1 \
	persist.radio.apm_sim_not_pwdn=1 \
	rild.libpath=/system/lib64/libsec-ril.so \
	rild.libpath2=/system/lib64/libsec-ril-dsds.so \
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
	net.tethering.noprovisioning=true 
