cmake_minimum_required(VERSION 3.19.0)

include(FetchContent)

FetchContent_Declare(
    vst3-cpack
    GIT_REPOSITORY http://www.github.com/hansen-audio/vst3-cpack.git
    GIT_TAG main
)

FetchContent_MakeAvailable(vst3-cpack)
