// Copyright(c) 2021 Hansen Audio.

#include "renegate_config.h"
#include "hao/audio_modules/audio_modules.h"

namespace hao {

//------------------------------------------------------------------------

// clang-format off
const plugin_base::parent_child_tree_def Config::COMPONENT_TREE_DEF   = {
    {
        Config::ComponentTags::kReneGate,
        Config::ComponentTags::kTranceGate
    }
};

const plugin_base::entity_component_def Config::ENTITY_COMPONENT_DEF = {
    {
        Config::ComponentTags::kTranceGate,
        audio_modules::ModuleTags::TranceGate
    }
};

// clang-format on

//------------------------------------------------------------------------
} // namespace hao
