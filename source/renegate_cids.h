//------------------------------------------------------------------------
// Copyright(c) 2021 Hansen Audio.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace ha {
//------------------------------------------------------------------------
static const Steinberg::FUID
    kRenegateProcessorUID(0xEC8C4504, 0xFF35529F, 0x997829E6, 0x0F5D8E18);
static const Steinberg::FUID
    kRenegateControllerUID(0x6CD125F9, 0xF91657D6, 0xB6A56C8E, 0x58680CE9);

#define renegateVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace ha
