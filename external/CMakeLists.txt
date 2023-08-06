cmake_minimum_required(VERSION 3.15.0)

if(NOT HA_GIT_REPOSITORY_URL)
    set(HA_GIT_REPOSITORY_URL "https://www.github.com")
endif()

add_subdirectory(plugin-base)
add_subdirectory(vst3-cpack)