// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/plugin_base/core/types.h"

namespace ha {

//------------------------------------------------------------------------
struct Config
{
    enum ComponentTags : plugin_base::IDType
    {
        kReneGate = 0,
        kTranceGate,
        kNumComponents
    };

    static const plugin_base::parent_child_tree_def COMPONENT_TREE_DEF;
    static const plugin_base::entity_component_def ENTITY_COMPONENT_DEF;
};

//------------------------------------------------------------------------
} // namespace ha
