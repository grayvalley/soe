project(eridanus)
set(CMAKE_CXX_STANDARD 14)

include_directories(inc)
include_directories(src)

set(HEADER_FILES
        inc/laniakea/eridanus/SOE.hh
        inc/laniakea/eridanus/SOEListener.hh
        inc/laniakea/eridanus/SOEParser.hh
        inc/laniakea/eridanus/SOEClient.hh
        inc/laniakea/eridanus/RFC6455.hh
        inc/laniakea/eridanus/sha1/sha1.hh
        )

set(SOURCE_FILES
        src/SOE.cc
        src/SOEParser.cc
        src/SOEClient.cc
        inc/laniakea/eridanus/SOEOrderEntry.hh)

add_library(eridanus STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(eridanus PROPERTIES LINKER_LANGUAGE CXX)

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
target_link_libraries(eridanus nlohmann_json::nlohmann_json)
include_directories(${virgo_SOURCE_DIR}/inc)
target_link_libraries(eridanus virgo)
