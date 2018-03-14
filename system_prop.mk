#
# Copyright (C) 2017 Fernando Von Arx <fer.vonarx@gmail.com>
# Copyright (C) 2017 Jesse Chan <cjx123@outlook.com>
# Copyright (C) 2017 Ivan Meler <i_ivan@windowslive.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

# Dalvik
#PRODUCT_PROPERTY_OVERRIDES += \
#    dalvik.vm.heapstartsize=8m \
#    dalvik.vm.heapgrowthlimit=384m \
#    dalvik.vm.heapsize=1024m \
#    dalvik.vm.heaptargetutilization=0.75 \
#    dalvik.vm.heapminfree=4m \
#    dalvik.vm.heapmaxfree=16m
#
# HWUI
#PRODUCT_PROPERTY_OVERRIDES += \
#    ro.hwui.texture_cache_size=72 \
#    ro.hwui.layer_cache_size=48 \
#    ro.hwui.r_buffer_cache_size=8 \
#    ro.hwui.path_cache_size=32 \
#    ro.hwui.gradient_cache_size=1 \
#    ro.hwui.drop_shadow_cache_size=6 \
#    ro.hwui.texture_cache_flushrate=0.4 \
#    ro.hwui.text_small_cache_width=1024 \
#    ro.hwui.text_small_cache_height=1024 \
#    ro.hwui.text_large_cache_width=2048 \
#    ro.hwui.text_large_cache_height=2048
#
# Network
# Define default initial receive window size in segments.
PRODUCT_PROPERTY_OVERRIDES += \
	net.tcp.default_init_rwnd=60

# misc
PRODUCT_PROPERTY_OVERRIDES += \
	media.stagefright.legacyencoder=1 \
	media.stagefright.less-secure=1 \
	ro.telephony.mms_data_profile=5 \
	persist.media.treble_omx=false

# sdcardfs
PRODUCT_PROPERTY_OVERRIDES += \
	ro.sys.sdcardfs=true

# USB
PRODUCT_PROPERTY_OVERRIDES += \
	ro.adb.secure=0
