//------------------------------------------------------------------------
//  Ready to Install page strings e.g.
//  VST3 Plugin will be installed to:
//    C:\....
//------------------------------------------------------------------------
#define VST3_STR "VST3"
#define VST3_PRESETS_STR "VST3 Presets"
#define PLUGIN_INSTALLED_TO_STR " Plugin will be installed to:"
#define PRESETS_INSTALLED_TO_STR " Presets will be installed to:"

function UpdateReadyMemo(Space, NewLine, MemoUserInfoInfo, MemoDirInfo, MemoTypeInfo, MemoComponentsInfo, MemoGroupInfo, MemoTasksInfo: String): String;
 var
    cTemp: String;
begin
  if WizardIsComponentSelected('Plugin')
  then begin
    cTemp := cTemp + '{#VST3_STR}{#PLUGIN_INSTALLED_TO_STR}' + NewLine;
    cTemp := cTemp + Space + ExpandConstant('{commoncf64}\{#VST3_STR}') + NewLine + NewLine;
  end;
  
  if WizardIsComponentSelected('Presets')
  then begin
    cTemp := cTemp + '{#VST3_STR}{#PRESETS_INSTALLED_TO_STR}' + NewLine;
    cTemp := cTemp + Space + ExpandConstant('{commonappdata}\{#VST3_PRESETS_STR}') + NewLine + NewLine;
  end;

  Result := cTemp;
end;