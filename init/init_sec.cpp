#include <stdio.h>
#include <stdlib.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

#include "init_sec.h"

#define MODEL_NAME_LEN 5  // e.g. "G935F"
#define BUILD_NAME_LEN 8  // e.g. "XXU1DQJ1"
#define CODENAME_LEN   11 // e.g. "hero2ltebmc"


static void property_override(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    const std::string bootloader = android::base::GetProperty("ro.bootloader", "");
    const std::string bl_model = bootloader.substr(0, MODEL_NAME_LEN);
    const std::string bl_build = bootloader.substr(MODEL_NAME_LEN);

    std::string model;  // G935F
    std::string device; // hero2lte
    std::string name;    // hero2ltebmc
    std::string description;
    std::string fingerprint;

    model = "SM-" + bl_model;

    for (size_t i = 0; i < VARIANT_MAX; i++) {
        std::string model_ = all_variants[i]->model;
        if (model.compare(model_) == 0) {
            device = all_variants[i]->codename;
            break;
        }
    }

    if (device.size() == 0) {
        LOG(ERROR) << "Could not detect device, forcing hero2lte";
        device = "hero2lte";
    }

    name = device + "xx";

    description = name + "-user 8.0.0 R16NW " + bl_model + bl_build + " release-keys";
    fingerprint = "samsung/" + name + "/" + device + ":8.0.0/R16NW/" + bl_model + bl_build + ":user/release-keys";

    LOG(INFO) << "Found bootloader: " << bootloader;
    LOG(INFO) << "Setting ro.product.model and ro.vendor.product.model: " << model;
    LOG(INFO) << "Setting ro.product.device and ro.vendor.product.device: " << device;
    LOG(INFO) << "Setting ro.product.name and ro.vendor.product.name: " << name;
    LOG(INFO) << "Setting ro.build.product and ro.vendor.build.product: " << device;
    LOG(INFO) << "Setting ro.build.description and ro.vendor.build.description: " << description;
    LOG(INFO) << "Setting ro.build.fingerprint and ro.vendor.build.fingerprint: " << fingerprint;

    property_override_dual("ro.product.model", "ro.vendor.product.model", model.c_str());
    property_override_dual("ro.product.device", "ro.vendor.product.device", device.c_str());
    property_override_dual("ro.product.name", "ro.vendor.product.name", name.c_str());
    property_override_dual("ro.build.product", "ro.vendor.build.product", device.c_str());
    property_override_dual("ro.build.description", "ro.vendor.build.description", description.c_str());
    property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", fingerprint.c_str());
}
