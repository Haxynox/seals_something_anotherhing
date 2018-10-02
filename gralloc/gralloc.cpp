/*
 * Copyright (C) 2018 Simon Shields <simon@lineageos.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "gralloc_wrap"
#include <cutils/properties.h>
#include <log/log.h>
#include <errno.h>
#include <hardware/hardware.h>
#include <hardware/gralloc.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#ifdef HAS_GRALLOC_PRIV
#include <gralloc_priv.h>
#endif

#ifdef __LP64__
#define OEM_GRALLOC "/system/lib64/hw/gralloc.vendor.exynos5.so"
#define OSS_GRALLOC "/system/lib64/hw/gralloc.exynos5.so"
#else
#define OEM_GRALLOC "/system/lib/hw/gralloc.vendor.exynos5.so"
#define OSS_GRALLOC "/system/lib/hw/gralloc.exynos5.so"
#endif

#define OSS_GRALLOC_PROPERTY "persist.gralloc.use_oss"

#define OEM_GRALLOC_CALL(action, args...) ((oem_gralloc_module && oem_gralloc_module->action) ?\
		oem_gralloc_module->action(oem_gralloc_module, args) : -ENOSYS);
#define OEM_ALLOC_CALL(action, args...) ((oem_alloc_device && oem_alloc_device->action) ?\
		oem_alloc_device->action(oem_alloc_device, args) : -ENOSYS);
/*
typedef int ion_user_handle_t;
struct private_handle_t {
	// 0x0-0xc
    struct native_handle nativeHandle;

    enum {
        PRIV_FLAGS_FRAMEBUFFER = 0x00000001,
        PRIV_FLAGS_USES_UMP    = 0x00000002,
        PRIV_FLAGS_USES_ION    = 0x00000020
    };

    // file-descriptors
    int     fd; //0xc
    int     fd1; //0x10
    int     fd2;//0x14
    // ints
    int     magic;//0x18
    int     flags;//0x1c
    int     size;//0x20
    int     offset;//0x24

    int     format;//0x28
    int     width;//0x2c
    int     height;//0x30
    int     stride;//0x34
    int     vstride;//0x38
    int     frameworkFormat;//0x3c

    ion_user_handle_t handle;//0x40
    ion_user_handle_t handle1;//0x44
    ion_user_handle_t handle2;//0x48

	//0x4c padding 

    // FIXME: the attributes below should be out-of-line
    uint64_t base __attribute__((aligned(8))); //0x50
    uint64_t base1 __attribute__((aligned(8))); //0x58
    uint64_t base2 __attribute__((aligned(8))); //0x60
};
*/
static void *oemGralloc;
static struct gralloc_module_t *oem_gralloc_module = NULL;
static struct alloc_device_t *oem_alloc_device = NULL;

#define dump_handle(hnd) _dump_handle(hnd, "f")
static void _dump_handle(buffer_handle_t handle, const char *func) {
#ifdef HAS_GRALLOC_PRIV
	private_handle_t *hnd = (private_handle_t *)handle;
	if (hnd->magic != 0x3141592) {
		ALOGW("invalid gralloc magic");
		return;
	}
	ALOGI("%s(hnd=%p) fds=(%d,%d,%d), base=(0x%lx,0x%lx,0x%lx), "
			"ion=(%d,%d,%d), flags=0x%x, size=%d/%d/%d, "
			"offset=%d, fmt=0x%x, unknown=0x%x, internal_fmt=0x%x, bit=%#x "
			"w/h=%d/%d, stride/vstride=%d/%d, fwkfmt=0x%x, numints=%d, numfds=%d, "
			"compressible=%d, "
			"unknown: %d/%d/%d/%d/%d/%d/%d, base=%#jx/%#jx/%#jx",
			func, handle, hnd->fd, hnd->fd1, hnd->fd2, (long)hnd->base, (long)hnd->base1, (long)hnd->base2,
			hnd->handle, hnd->handle1, hnd->handle2, hnd->flags, hnd->size, hnd->size1, hnd->size2,
			hnd->offset, hnd->format, hnd->__unknown2, hnd->internal_format, hnd->format_top_bit,
			hnd->width, hnd->height, hnd->stride, hnd->vstride, hnd->frameworkFormat, hnd->numInts, hnd->numFds,
			hnd->is_compressible,
			hnd->__unknown2, hnd->__unknown3, hnd->__unknown4, hnd->__unknown5, hnd->__unknown6,
			hnd->compressed_out, hnd->prefer_compression, hnd->base, hnd->base1, hnd->base2);
#endif

}

static void ensure_gralloc_open(void) {
	if (oemGralloc && oem_gralloc_module)
		return;

	int ret;
	const char *gralloc_path = OEM_GRALLOC;

	ret = property_get_bool(OSS_GRALLOC_PROPERTY, false);
	if (ret) {
		ALOGE("Using OSS gralloc");
		gralloc_path = OSS_GRALLOC;
	} else {
		ALOGE("Not using OSS gralloc");
	}

	oemGralloc = dlopen(gralloc_path, RTLD_NOW);
	if (oemGralloc == NULL) {
		ALOGE("Failed to open %s: %s", gralloc_path, dlerror());
		return;
	}

	oem_gralloc_module = (struct gralloc_module_t *)dlsym(oemGralloc, HAL_MODULE_INFO_SYM_AS_STR);
	if (oem_gralloc_module == NULL) {
		ALOGE("Failed to find symbol '%s': %s", HAL_MODULE_INFO_SYM_AS_STR, dlerror());
	}
}

static int wrap_register_buffer(struct gralloc_module_t const* module,
		buffer_handle_t handle) {
	ensure_gralloc_open();
	int ret = OEM_GRALLOC_CALL(registerBuffer, handle);
	ALOGI("register_buffer(hnd=%p) => %d", handle, ret);
	return ret;
}

static int wrap_unregister_buffer(struct gralloc_module_t const* module,
		buffer_handle_t handle) {
	ensure_gralloc_open();
	return OEM_GRALLOC_CALL(unregisterBuffer, handle);
}

static int wrap_lock(struct gralloc_module_t const* module, buffer_handle_t handle, int usage,
		int l, int t, int w, int h, void** vaddr) {
	ensure_gralloc_open();
	ALOGI("lock(hnd=%p): %p usage(0x%x), l/t(%d/%d), w/h(%d/%d)",
			handle, oem_gralloc_module->lock, usage, l, t, w, h);
	int ret = OEM_GRALLOC_CALL(lock, handle, usage, l, t, w, h, vaddr);
	dump_handle(handle);
	ALOGI("lock(hnd=%p): ret=%d. vaddr = {%p, %p, %p}", handle, ret, vaddr[0], vaddr[1], vaddr[2]);
	return ret;
}

static int wrap_unlock(struct gralloc_module_t const* module,
		buffer_handle_t handle) {
	ensure_gralloc_open();
	return OEM_GRALLOC_CALL(unlock, handle);
}

static int wrap_lock_ycbcr(struct gralloc_module_t const* module, buffer_handle_t handle, int usage,
		int l, int t, int w, int h, struct android_ycbcr *ycbcr) {
	ensure_gralloc_open();
	private_handle_t *hnd = (private_handle_t *)handle;
	ALOGI("lock_ycbcr(hnd=%p): usage(0x%x), l/t(%d/%d), w/h(%d/%d). hnd{w=%d,h=%d,base=%#lx}",
			handle, usage, l, t, w, h, hnd->width, hnd->height, (unsigned long )hnd->base);
	int ret = OEM_GRALLOC_CALL(lock_ycbcr, handle, usage, l, t, w, h, ycbcr);
	ALOGI("lock_ycbcr(hnd=%p): ret=%d, ycbcr{y=%p,cb=%p,cr=%p,ystride=%zu,cstride=%zu,chroma_step=%zu}",
			handle, ret, ycbcr->y, ycbcr->cb, ycbcr->cr, ycbcr->ystride, ycbcr->cstride, ycbcr->chroma_step);

#if 0
	int *mod = (int *)oem_gralloc_module;
	struct private_module_t *priv = (struct private_module_t *)mod;
	for (size_t i = 0; i < sizeof(struct private_module_t)/sizeof(int); i++) {
		if (&mod[i] == (int *)&priv->ionfd) {
			ALOGE("%#x: %#x - IONFD", (unsigned int)(i*sizeof(int)), mod[i]);
		} else {
#if 0
			if (mod[i] == 0)
				mod[i] = i;
#endif
			ALOGE("%#x: %#x .", (unsigned int)(i*sizeof(int)), mod[i]);
		}
	}
#endif
	return ret;
}

int wrap_alloc(struct alloc_device_t* dev, int w, int h, int format, int usage,
		buffer_handle_t* handle, int* stride) {
	if (usage & GRALLOC_USAGE_HW_MASK) {
		ALOGI("Calling alloc(hnd=%p): w(%d), h(%d), fmt(0x%x), usage(0x%x)",
				handle, w, h, format, usage);
		int ret = OEM_ALLOC_CALL(alloc, w, h, format, usage, handle, stride);
		if (!ret) {
			dump_handle(*handle);
		}

end:
		ALOGI("alloc(hnd=%p) returns ret(%d), stride(%d)", handle, ret, *stride);
		return ret;
	} else {
		return OEM_ALLOC_CALL(alloc, w, h, format, usage, handle, stride);
	}
}

int wrap_free(struct alloc_device_t* dev, buffer_handle_t handle) {
	return OEM_ALLOC_CALL(free, handle);
}

static int wrap_close(struct hw_device_t *dev) {
	return oem_alloc_device->common.close(dev);
}

int gralloc_wrap_open(const struct hw_module_t *module, const char *id,
		struct hw_device_t **device) {
	int ret = 0;
	const char *gralloc_path = OEM_GRALLOC;
	struct alloc_device_t *wrapper;

	ret = property_get_bool(OSS_GRALLOC_PROPERTY, false);
	if (ret) {
		ALOGE("Using OSS gralloc");
		gralloc_path = OSS_GRALLOC;
	} else {
		ALOGE("Not using OSS gralloc");
	}

	ensure_gralloc_open();
	if (!oemGralloc || !oem_gralloc_module)
		return -ENOSYS;

	/* vendor open */
	if (!strcmp(id, GRALLOC_HARDWARE_GPU0)) {
		/* we only care about GPU0 */
		ret = oem_gralloc_module->common.methods->open((struct hw_module_t *)oem_gralloc_module, id, (struct hw_device_t **)&oem_alloc_device);
		if (ret < 0) {
			ALOGE("oem gralloc open failed: %d", ret);
			return ret;
		}

		wrapper = (struct alloc_device_t *)calloc(1, sizeof(*wrapper));
		if (!wrapper) {
			ALOGE("wrapper allocate failed: %d", errno);
			return -ENOMEM;
		}

		wrapper->common.tag = HARDWARE_DEVICE_TAG;
		wrapper->common.version = 0;
		wrapper->common.module = (struct hw_module_t *)module;
		wrapper->common.close = wrap_close;
		wrapper->alloc = wrap_alloc;
		wrapper->free = wrap_free;
		wrapper->dump = NULL;

		*device = (struct hw_device_t *)wrapper;
		ALOGI("returned device!");
	} else {
		// TODO: cleanup
		return oem_gralloc_module->common.methods->open((struct hw_module_t *)oem_gralloc_module, id, device);
	}


	return 0;
}

static struct hw_module_methods_t gralloc_module_methods = {
	.open = gralloc_wrap_open,
};

struct gralloc_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = GRALLOC_MODULE_API_VERSION_0_2,
		.hal_api_version = 0,
		.id = GRALLOC_HARDWARE_MODULE_ID,
		.name = "Gralloc Wrapper HAL",
		.author = "Simon Shields",
		.methods = &gralloc_module_methods,
	},
	.registerBuffer = wrap_register_buffer,
	.unregisterBuffer = wrap_unregister_buffer,
	.lock = wrap_lock,
	.unlock = wrap_unlock,
	.perform = NULL,
	.lock_ycbcr = wrap_lock_ycbcr,
};
