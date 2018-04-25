#ifndef INIT_SEC_H
#define INIT_SEC_H

#include <string.h>

enum device_variant {
    VARIANT_G935F = 0,
    VARIANT_G935W8,
    VARIANT_G935K,
    VARIANT_G935L,
    VARIANT_G935S,
    VARIANT_G930F,
    VARIANT_G930W8,
    VARIANT_G930K,
    VARIANT_G930L,
    VARIANT_G930S,
    VARIANT_MAX
};

typedef struct {
    std::string model;
    std::string codename;
} variant;

static const variant edge_international_models = {
    .model = "SM-G935F",
    .codename = "hero2lte"
};

static const variant edge_canada_models = {
    .model = "SM-G935W8",
    .codename = "hero2ltebmc"
};

static const variant edge_korea_docomo_models = {
    .model = "SM-G935K",
    .codename = "hero2ltektt"
};

static const variant edge_korea_uplus_models = {
    .model = "SM-G935L",
    .codename = "hero2ltelgt"
};

static const variant edge_korea_telecom_models = {
    .model = "SM-G935S",
    .codename = "hero2lteskt"
};

static const variant international_models = {
    .model = "SM-G930F",
    .codename = "herolte"
};

static const variant canada_models = {
    .model = "SM-G930W8",
    .codename = "heroltebmc"
};

static const variant korea_docomo_models = {
    .model = "SM-G930K",
    .codename = "heroltektt"
};

static const variant korea_uplus_models = {
    .model = "SM-G930L",
    .codename = "heroltelgt"
};

static const variant korea_telecom_models = {
    .model = "SM-G930S",
    .codename = "herolteskt"
};

static const variant *all_variants[VARIANT_MAX] = {
    &edge_international_models,
    &edge_canada_models,
    &edge_korea_docomo_models,
    &edge_korea_uplus_models,
    &edge_korea_telecom_models,
    &international_models,
    &canada_models,
    &korea_docomo_models,
    &korea_uplus_models,
    &korea_telecom_models,
};

#endif // INIT_SEC_H
