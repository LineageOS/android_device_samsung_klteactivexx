/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Copyright (c) 2018-2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "init_msm8974.h"

using android::base::GetProperty;

void vendor_load_properties()
{
    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("G870F") == 0) {
        /* klteactivexx */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/klteactivexx/klteactive:5.0/LRX21T/G870FXXU1BQE1:user/release-keys");
        property_override("ro.build.description", "klteactivexx-user 5.0 LRX21T G870FXXU1BQE1 release-keys");
        property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-G870F");
        property_override_dual("ro.product.device", "ro.product.vendor.device", "klteactivexx");
    } else if (bootloader.find("G870A") == 0) {
        /* klteattactive */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/klteattactive/klteattactive:6.0.1/MMB29M/G870AUCS2DPK7:user/release-keys");
        property_override("ro.build.description", "klteattactive-user 6.0.1 MMB29M G870AUCS2DPK7 release-keys");
        property_override_dual("ro.product.model", "ro.product.vendor.model", "SM-G870A");
        property_override_dual("ro.product.device", "ro.product.vendor.device", "klteattactive");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
            << device <<  " device" << std::endl;
}
