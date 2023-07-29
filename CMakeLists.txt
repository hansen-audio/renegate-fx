cmake_minimum_required(VERSION 3.14.0)

project(ReneGate
    VERSION 2022.09
    DESCRIPTION "VST 3 Trancegate Effect"
)
  
add_subdirectory(external)

smtg_enable_vst3_sdk()

smtg_add_vst3plugin(ReneGate     
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

target_sources(ReneGate
    PRIVATE
        resource/renegate_editor.uidesc
)
target_link_libraries(ReneGate
    PRIVATE
        vstgui_support
)
smtg_target_add_plugin_resources(ReneGate 
    RESOURCES
        "resource/renegate_editor.uidesc"
)

smtg_target_add_plugin_snapshots(ReneGate
    RESOURCES
        resource/EC8C4504FF35529F997829E60F5D8E18_snapshot.png
        resource/EC8C4504FF35529F997829E60F5D8E18_snapshot_2.0x.png
)

target_link_libraries(ReneGate
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
    smtg_set_bundle(ReneGate INFOPLIST 
        "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" 
        PREPROCESS
    )
elseif(SMTG_WIN)
    target_sources(ReneGate PRIVATE 
        resource/win32resource.rc
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ReneGate)
	
	set_target_properties(ReneGate PROPERTIES
		VS_DEBUGGER_COMMAND
			"$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
		VS_DEBUGGER_COMMAND_ARGUMENTS
			" --pluginfolder \"$(OutDir)\" "
	)
endif()

get_target_property(PLUGIN_PACKAGE_PATH ReneGate SMTG_PLUGIN_PACKAGE_PATH)   

include(CPackComponent)
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_PACKAGE_VENDOR "Hansen Audio")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
cpack_add_install_type(full DISPLAY_NAME "Full installation")

if(WIN32)
	cpack_add_component(plugin
		DISPLAY_NAME "VST3 Plugin"
		INSTALL_TYPES full
	)

	install(
		DIRECTORY "${PLUGIN_PACKAGE_PATH}"
		DESTINATION "VST3"
		COMPONENT plugin
	)

	cpack_add_component(presets
		DISPLAY_NAME "VST3 Presets"
		INSTALL_TYPES full
	)

	install(
		DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/content/VST3 Presets"
		DESTINATION "."
		COMPONENT presets
	)
	
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_VENDOR}/${PROJECT_NAME}")
	
	set(CPACK_COMPONENTS_ALL plugin presets)
	
	# Inno Setup component specific
	set(CPACK_INNOSETUP_plugin_INSTALL_DIRECTORY "{commoncf64}")
	set(CPACK_INNOSETUP_presets_INSTALL_DIRECTORY "{commonappdata}")
	
	# Inno Setup global
    set(CPACK_GENERATOR "INNOSETUP")
	set(CPACK_INNOSETUP_SETUP_AppId "{{C6695644-EA21-4EF5-BB3D-94EE2343A47E}}")
	set(CPACK_INNOSETUP_ALLOW_CUSTOM_DIRECTORY OFF)
	set(CPACK_INNOSETUP_CODE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/installer/UpdateReadyMemo.pas")
else()
    # On Linux, just zip a tar.gz file which includes the plugin and the presets
	install(
		DIRECTORY "${PLUGIN_PACKAGE_PATH}"
		DESTINATION "."
		COMPONENT package
	)

	install(
		DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/content/VST3 Presets"
		DESTINATION "."
		COMPONENT package
	)

    install(
        FILES "${CPACK_RESOURCE_FILE_LICENSE}"
        DESTINATION "."
        COMPONENT package
    )
	
    set(CPACK_GENERATOR "TGZ")
	set(CPACK_COMPONENTS_ALL package)

    # tar.gz file name, e.g. myplugin-1.0.0-linux.tar.gz
    string(TOUPPER package package_UPPER)
    set(CPACK_ARCHIVE_${package_UPPER}_FILE_NAME "${PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
endif()    

include(CPack)