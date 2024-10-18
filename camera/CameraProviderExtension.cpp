/*
 * Copyright (C) 2024 LibreMobileOS Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CameraProviderExtension.h"

#include <fstream>

#define TORCH_BRIGHTNESS "torch_brightness"
#define TORCH_MAX_BRIGHTNESS "torch_max_brightness"

static std::string kTorchLedPaths[] = {
        "/sys/devices/platform/11d00000.i2c5/i2c-5/5-0034/mt6360_pmu_fled.3.auto/mt6360_pmu_fled.0/rt-flash-led.0/flashlight/mt-flash-led1",
        "/sys/devices/platform/11d00000.i2c5/i2c-5/5-0034/mt6360_pmu_fled.3.auto/mt6360_pmu_fled.1/rt-flash-led.1/flashlight/mt-flash-led2",
};

/**
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

/**
 * Read value from the path and close file.
 */
template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

bool supportsTorchStrengthControlExt() {
    return true;
}

int32_t getTorchDefaultStrengthLevelExt() {
    return 7;
}

int32_t getTorchMaxStrengthLevelExt() {
    // In our device, both LEDs has same maximum value
    // so get from one.
    auto node = kTorchLedPaths[0] + "/" + TORCH_MAX_BRIGHTNESS;
    return get(node, 0);
}

int32_t getTorchStrengthLevelExt() {
    // We write same value in the both LEDs,
    // so get from one.
    auto node = kTorchLedPaths[0] + "/" + TORCH_BRIGHTNESS;
    return get(node, 0);
}

void setTorchStrengthLevelExt(int32_t torchStrength) {
    for (auto& path : kTorchLedPaths) {
        auto node = path + "/" + TORCH_BRIGHTNESS;
        set(node, torchStrength);
    }
}
