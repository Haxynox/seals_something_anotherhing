# Packages
PRODUCT_PACKAGES += \
	libion_exynos \
	libfimg \
	android.hardware.graphics.allocator@2.0-impl \
	android.hardware.graphics.allocator@2.0-service \
	android.hardware.graphics.composer@2.1-impl \
	android.hardware.graphics.mapper@2.0-impl \
	libhwc2on1adapter
#	libExynosHWCService 
#	libion
#	gralloc.exynos5

# RenderScript HAL
PRODUCT_PACKAGES += \
	android.hardware.renderscript@1.0-impl

# DRM
PRODUCT_PACKAGES += \
	android.hardware.drm@1.0-impl

# Not shims you are looking for
PRODUCT_PACKAGES += \
	libprocname

# Permissions
PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.vulkan.level-0.xml:system/etc/permissions/android.hardware.vulkan.level.xml \
	frameworks/native/data/etc/android.hardware.vulkan.version-1_0_3.xml:system/etc/permissions/android.hardware.vulkan.version.xml

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
	ro.bq.gpu_to_cpu_unsupported=1 \
	ro.opengles.version=196609 \
	ro.sf.lcd_density=560 \
	debug.hwc.force_gpu=1 \
	debug.hwui.use_buffer_age=false

# Properties - HWC - not used on lineage/aosp
PRODUCT_PROPERTY_OVERRIDES += \
	debug.hwc.winupdate=1 \
	debug.hwc.otf=1

# HWC
#PRODUCT_PROPERTY_OVERRIDES += \
#	debug.hwc.force_gpu=0 \
#	debug.hwc.max_hw_overlays=0 \
#	debug.egl.hw=1 \
#	debug.sf.enable_hwc_vds=1 \
#	debug.sf.hw=1 \
#	debug.slsi_platform=1 \
#	debug.hwc.winupdate=1 \
#	ro.hardware.egl=mali \
#	debug.hwui.use_buffer_age=false \
#	persist.sys.ui.hw=true 
#

