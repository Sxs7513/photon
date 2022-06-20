cmake_minimum_required(VERSION 2.8)

# set(QUICKJS_PATH /home/sxs/quickjs-master/quickjs-master)
set(QUICKJS_PATH ./runtime/deps/quickjs)
set(LIBUV_PATH /home/sxs/libuv)
set(CMAKE_PREFIX_PATH /opt/Qt5.12.9/5.12.9/gcc_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "-O0 -Wall -g -ggdb")

find_package(Qt5 COMPONENTS Widgets Gui Core Svg REQUIRED)

add_subdirectory(runtime) 
add_subdirectory(render)

add_executable(Main
    ./utils/utils.c
    ./engine/engineUtils.cpp
    ./engine/engine.cpp
)

include_directories(
    ${LIBUV_PATH}/include
    ${QUICKJS_PATH}/include
    utils
    engine
    runtime
    render/native
)

target_link_libraries(Main runtime render dl pthread)

add_custom_command(OUTPUT test-render.js
    COMMAND npm run ui -- --outfile=./test/test-render.js
)

add_custom_target(JSUI ALL DEPENDS test-render.js)

add_dependencies(Main JSUI)
