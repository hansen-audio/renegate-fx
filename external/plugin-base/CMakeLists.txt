cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    plugin-base
    GIT_REPOSITORY ${HA_GIT_REPOSITORY_URL}/hansen-audio/plugin-base.git
    GIT_TAG origin/master
)

FetchContent_MakeAvailable(plugin-base)