# Camera
BOARD_USE_SAMSUNG_CAMERAFORMAT_NV21 := true
TARGET_SPECIFIC_CAMERA_PARAMETER_LIBRARY := libcamera_parameters_hero

TARGET_LD_SHIM_LIBS += \
    /system/lib64/libexynoscamera.so|/system/lib64/libstagefright_shim.so \
    /system/lib/libexynoscamera.so|/system/lib/libstagefright_shim.so