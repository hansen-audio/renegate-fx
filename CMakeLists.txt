cmake_minimum_required(VERSION 3.14.0)

project(renegate
    VERSION 2022.09
    DESCRIPTION "VST 3 Trancegate Effect"
)
  
add_subdirectory(external)

smtg_enable_vst3_sdk()

smtg_add_vst3plugin(renegate     
    source/renegate_cids.h
    source/renegate_config.cpp
    source/renegate_config.h
    source/renegate_controller.cpp
    source/renegate_controller.h
    source/renegate_entry.cpp
    source/renegate_processor.cpp
    source/renegate_processor.h
    source/version.h
)

target_sources(renegate
    PRIVATE
        resource/renegate_editor.uidesc
)
target_link_libraries(renegate
    PRIVATE
        vstgui_support
)
smtg_target_add_plugin_resources(renegate 
    RESOURCES
        "resource/renegate_editor.uidesc"
)

smtg_target_add_plugin_snapshots(renegate
    RESOURCES
        resource/EC8C4504FF35529F997829E60F5D8E18_snapshot.png
        resource/EC8C4504FF35529F997829E60F5D8E18_snapshot_2.0x.png
)

target_link_libraries(renegate
    PRIVATE
        plugin-base
        audio-modules
)

set_property(
    TARGET 
        audio-modules
        plugin-base
        fx-collection 
    PROPERTY 
        POSITION_INDEPENDENT_CODE ON
)

if(SMTG_MAC)
    smtg_set_bundle(renegate INFOPLIST 
        "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" 
        PREPROCESS
    )
elseif(SMTG_WIN)
    target_sources(renegate PRIVATE 
        resource/win32resource.rc
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT renegate)
	
	set_target_properties(renegate PROPERTIES
		VS_DEBUGGER_COMMAND
			"$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
		VS_DEBUGGER_COMMAND_ARGUMENTS
			" --pluginfolder \"$(OutDir)\" "
	)
endif()


