//------------------------------------------------------------------------
// Copyright(c) 2021 Hansen Audio.
//------------------------------------------------------------------------

#include "renegate_processor.h"
#include "renegate_cids.h"
#include "renegate_config.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/ivstprocesscontext.h"

#include "ha/plugin_base/common/audio_module_visitor.h"
#include "ha/plugin_base/vst3/component/audio_processing.h"
#include "ha/plugin_base/vst3/component/audio_setup.h"

using namespace Steinberg;

namespace ha {

//------------------------------------------------------------------------
// RenegateProcessor
//------------------------------------------------------------------------
RenegateProcessor::RenegateProcessor()
{
    //--- set the wanted controller for our processor
    setControllerClass(kRenegateControllerUID);
}

//------------------------------------------------------------------------
RenegateProcessor::~RenegateProcessor() {}

//------------------------------------------------------------------------
tresult PLUGIN_API RenegateProcessor::initialize(FUnknown* context)
{
    // Here the Plug-in will be instanciated

    //---always initialize the parent-------
    tresult result = AudioEffect::initialize(context);
    // if everything Ok, continue
    if (result != kResultOk)
    {
        return result;
    }

    //--- create Audio IO ------
    addAudioInput(STR16("Stereo In"), Vst::SpeakerArr::kStereo);
    addAudioOutput(STR16("Stereo Out"), Vst::SpeakerArr::kStereo);

    plugin_base::common::setup_context(component_context,
                                       Config::ENTITY_COMPONENT_DEF,
                                       Config::COMPONENT_TREE_DEF);

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API RenegateProcessor::terminate()
{
    // Here the Plug-in will be de-instanciated, last possibility to remove some
    // memory!

    //---do not forget to call parent ------
    return AudioEffect::terminate();
}

//------------------------------------------------------------------------
tresult PLUGIN_API RenegateProcessor::setActive(TBool state)
{
    //--- called when the Plug-in is enable/disable (On/Off) -----
    return AudioEffect::setActive(state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API RenegateProcessor::process(Vst::ProcessData& data)
{
    //--- First : Read inputs parameter changes-----------

    bool bRes = plugin_base::vst3::process_audio(component_context, data);
    if (!bRes)
        return kResultFalse;

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API
RenegateProcessor::setupProcessing(Vst::ProcessSetup& newSetup)
{
    bool bRes =
        plugin_base::vst3::setup_processing(component_context, newSetup, this);
    if (!bRes)
        return kResultFalse;

    //--- called before any processing ----
    return AudioEffect::setupProcessing(newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API
RenegateProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
    // by default kSample32 is supported
    if (symbolicSampleSize == Vst::kSample32)
        return kResultTrue;

    // disable the following comment if your processing support kSample64
    /* if (symbolicSampleSize == Vst::kSample64)
        return kResultTrue; */

    return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API RenegateProcessor::setState(IBStream* state)
{
    // called when we load a preset, the model has to be reloaded
    IBStreamer streamer(state, kLittleEndian);

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API RenegateProcessor::getState(IBStream* state)
{
    // here we need to save the model
    IBStreamer streamer(state, kLittleEndian);

    return kResultOk;
}

//------------------------------------------------------------------------
} // namespace ha
