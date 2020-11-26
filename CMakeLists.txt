project(soe)
set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
include_directories(src)

set(HEADER_FILES
        inc/grayvalley/soe/SOE.hh
        inc/grayvalley/soe/SOEListener.hh
        inc/grayvalley/soe/SOEParser.hh
        inc/grayvalley/soe/SOEClient.hh
        inc/grayvalley/soe/SOEOrderEntry.hh
        inc/grayvalley/soe/RFC6455.hh
        inc/grayvalley/soe/sha1/sha1.hh
        )

set(SOURCE_FILES
        src/SOE.cc
        src/SOEParser.cc
        src/SOEClient.cc
        )

add_library(soe STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(soe PROPERTIES LINKER_LANGUAGE CXX)

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        )
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
    include_directories(${json_SOURCE_DIR})
endif()
target_link_libraries(soe nlohmann_json::nlohmann_json)
include_directories(${core_SOURCE_DIR}/inc)
target_link_libraries(soe core)
