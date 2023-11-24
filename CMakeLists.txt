cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)
project(gtest_suite LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# main executable
add_executable(main src/main.cpp)
target_sources(main PUBLIC 
    src/ResourceManager.cpp 
    src/UI.cpp
    src/UIElement.cpp
)
target_link_libraries(main PRIVATE sfml-graphics)
target_link_libraries(main PRIVATE sfml-audio)
target_link_libraries(main PRIVATE sfml-network)
target_link_libraries(main PRIVATE sfml-window)
target_link_libraries(main PRIVATE sfml-system)

target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/../include)

target_compile_features(main PRIVATE cxx_std_17)
target_compile_definitions( main PUBLIC LOG_LEVEL=${LOG_LEVEL} )

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

# gtest_suite executable
enable_testing()
add_executable(gtest_suite EXCLUDE_FROM_ALL test/main.cpp)
target_sources(gtest_suite PUBLIC 
    src/ResourceManager.cpp 
    src/UI.cpp
    src/UIElement.cpp
    test/Test_UI.cpp
)
target_link_libraries(gtest_suite PRIVATE sfml-graphics)
target_link_libraries(gtest_suite PRIVATE sfml-audio)
target_link_libraries(gtest_suite PRIVATE sfml-network)
target_link_libraries(gtest_suite PRIVATE sfml-window)
target_link_libraries(gtest_suite PRIVATE sfml-system)
target_link_libraries(gtest_suite PRIVATE GTest::gtest_main)

target_include_directories(gtest_suite PRIVATE ${CMAKE_BINARY_DIR}/../include)

target_compile_features(gtest_suite PRIVATE cxx_std_17)
target_compile_definitions( gtest_suite PUBLIC LOG_LEVEL=${LOG_LEVEL} )

include(GoogleTest)
gtest_discover_tests(gtest_suite)

if(WIN32)
    add_custom_command(
        TARGET gtest_suite
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

install(TARGETS main)