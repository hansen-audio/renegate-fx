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

if(WIN32)
    get_target_property(PLUGIN_PACKAGE_PATH ReneGate SMTG_PLUGIN_PACKAGE_PATH)
    install(
        DIRECTORY "${PLUGIN_PACKAGE_PATH}"
        # Does not work yet!!! We cannot access Inno's {commoncf64}
        DESTINATION "../Common Files/VST3"
        COMPONENT ${PROJECT_NAME}
    )

    set(CPACK_GENERATOR "INNOSETUP")
    set(CPACK_PACKAGE_VENDOR "Hansen Audio")
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
    set(CPACK_COMPONENTS_ALL ${PROJECT_NAME})
    set(CPACK_VERBATIM_VARIABLES YES)
    include(CPack)
else()
    get_target_property(PLUGIN_PACKAGE_PATH ReneGate SMTG_PLUGIN_PACKAGE_PATH)
    install(
        DIRECTORY "${PLUGIN_PACKAGE_PATH}"
        DESTINATION "."
        COMPONENT ${PROJECT_NAME}
    )

    string(TOUPPER ${CMAKE_PROJECT_NAME} CMAKE_PROJECT_NAME_UPPER)
    set(CPACK_ARCHIVE_${CMAKE_PROJECT_NAME_UPPER}_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_PACKAGE_VENDOR "Hansen Audio")
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
    set(CPACK_COMPONENTS_ALL ${PROJECT_NAME})
    set(CPACK_VERBATIM_VARIABLES YES)
    include(CPack)
endif()
