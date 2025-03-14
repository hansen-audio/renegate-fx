cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    plugin-base
    GIT_REPOSITORY https://github.com/hansen-audio/plugin-base.git
    GIT_TAG main
)

FetchContent_MakeAvailable(plugin-base)