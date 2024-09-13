#
# Copyright (C) 2023 LibreMobileOS Foundation
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from device makefile.
$(call inherit-product, device/daria/zahedan/device.mk)

# Inherit some common LMODroid stuff.
$(call inherit-product, vendor/lmodroid/config/common_full_phone.mk)

PRODUCT_NAME := lmodroid_zahedan
PRODUCT_DEVICE := zahedan
PRODUCT_MANUFACTURER := Daria
PRODUCT_BRAND := Daria
PRODUCT_MODEL := DM-B50104

PRODUCT_SYSTEM_NAME := zahedan

PRODUCT_BUILD_PROP_OVERRIDES += \
    DeviceProduct=$(PRODUCT_SYSTEM_NAME)

BUILD_FINGERPRINT := Daria/zahedan/zahedan:13/TQ2A.230505.002/V4.43.1.1.BOND:user/release-keys

PRODUCT_GMS_CLIENTID_BASE := android-jimi
