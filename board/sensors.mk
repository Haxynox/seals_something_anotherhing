# Sensors
TARGET_NO_SENSOR_PERMISSION_CHECK := true

TARGET_LD_SHIM_LIBS += \
	/system/lib64/hw/fingerprint.vendor.exynos5.so|/vendor/lib64/libbauthtzcommon_shim.so
