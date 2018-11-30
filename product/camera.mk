DEVICE_PATH := device/samsung/hero-common

PRODUCT_PACKAGES += \
	libexynoscamera_shim  \
	camera.device@3.2-impl \
	camera.device@1.0-impl \
	android.hardware.camera.provider@2.4-impl \
	android.hardware.camera.provider@2.4-service \
	Camera2

PRODUCT_COPY_FILES += \
    $(DEVICE_PATH)/configs/camera/external_camera_config.xml:system/vendor/etc/external_camera_config.xml

