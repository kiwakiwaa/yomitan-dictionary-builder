cmake_minimum_required(VERSION 3.31)
project(
        yomitan_dictionary_builder
        VERSION 0.0.1
)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Glaze (json library)
FetchContent_Declare(
        glaze
        GIT_REPOSITORY https://github.com/stephenberry/glaze.git
        GIT_TAG main
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glaze)

# Google Test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# yaml cpp
include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

file(GLOB_RECURSE parser_headers "include/yomitan_dictionary_builder/parsers/*/*.h")
file(GLOB_RECURSE parser_sources "src/parsers/*/*.cpp")


add_library(yomitan_dictionary_builder_lib STATIC
        ${parser_sources}
        src/config/config_loader.cpp
        src/config/parser_registry.cpp
        src/core/dictionary/dicentry.cpp
        src/core/dictionary/html_element.cpp
        src/core/dictionary/yomitan_dictionary.cpp
        src/core/base_parser.cpp
        src/core/xml_parser.cpp
        src/core/yomitan_parser.cpp
        src/utils/jptools/kanji_utils.cpp
        src/utils/jptools/kana_convert.cpp
        src/index/index_reader.cpp
        src/index/jukugo_index_reader.cpp
        src/strategies/link/mdict_link_handling_strategy.cpp
        src/strategies/link/nds_link_extraction_strategy.cpp
        src/strategies/key/kjt_extraction_strategy.cpp
        src/strategies/image/image_handling_strategy.cpp
        src/strategies/image/hashed_image_strategy.cpp
        src/config/strategy_factory.cpp
        src/parsers/MDict/subitem_processor.cpp
        src/parsers/MDict/mdict_exporter.cpp
        src/core/asset_manager.cpp
        lib/pugixml.cpp
)

target_include_directories(yomitan_dictionary_builder_lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        lib
        ${glaze_SOURCE_DIR}/include
        ${yaml-cpp_SOURCE_DIR}/include
)

# Main Executable
add_executable(yomitan_dictionary_builder src/main.cpp)

target_link_libraries(yomitan_dictionary_builder PRIVATE
        yomitan_dictionary_builder_lib
        glaze::glaze
        yaml-cpp::yaml-cpp
)

# Tests executable
enable_testing()
add_executable(yomitan_dictionary_tests
        test/html_element_test.cpp
        test/json_test.cpp
        test/kanji_utils_test.cpp
        test/kana_convert_test.cpp
        test/index_reader_test.cpp
)

target_link_libraries(yomitan_dictionary_tests PRIVATE
        yomitan_dictionary_builder_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(yomitan_dictionary_tests DISCOVERY_TIMEOUT 300)
