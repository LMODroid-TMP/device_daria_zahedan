/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "UdfpsHandler.h"

#include <unistd.h>

class XiaomiUdfpsHander : public UdfpsHandler {
  public:
    void init(fingerprint_device_t *device) {
        mDevice = device;
        goodixExtCmd = reinterpret_cast<int32_t (*)(struct fingerprint_device __unused *, uint32_t, uint32_t)>(mDevice->reserved[0]);
    }

    void onFingerDown(uint32_t /*x*/, uint32_t /*y*/, float /*minor*/, float /*major*/) {
        usleep(50*1000);
        goodixExtCmd(0, 1, 0);
    }

    void onFingerUp() {
        goodixExtCmd(0, 0, 0);
    }

    void onAcquired(int32_t result, int32_t /*vendorCode*/) {
       // Nothing
    }

    void preEnroll() {
        // Nothing
    }

    void enroll() {
        // Nothing
    }

    void postEnroll() {
        // Nothing
    }

    void cancel() {
        // nothing
        goodixExtCmd(0, 0, 0);
    }

  private:
    fingerprint_device_t *mDevice;
    int32_t (*goodixExtCmd)(struct fingerprint_device __unused *, uint32_t, uint32_t);
};

static UdfpsHandler* create() {
    return new XiaomiUdfpsHander();
}

static void destroy(UdfpsHandler* handler) {
    delete handler;
}

extern "C" UdfpsHandlerFactory UDFPS_HANDLER_FACTORY = {
    .create = create,
    .destroy = destroy,
};
