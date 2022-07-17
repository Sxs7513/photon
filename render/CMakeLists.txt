cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS(-DDEBUG)
set(CMAKE_CXX_FLAGS "-O0 -Wall -g -ggdb")

set(ENGINE_PATH ../engine)
set(RUNTIME_PATH ../runtime)
set(QUICKJS_PATH /home/sxs/quickjs-master/quickjs-master)
set(LIBUV_PATH /home/sxs/libuv)
set(CMAKE_PREFIX_PATH /opt/Qt5.12.9/5.12.9/gcc_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Gui Core Svg REQUIRED)

add_library(render SHARED
    ./native/deps/yoga/log.cpp
    ./native/deps/yoga/Utils.cpp
    ./native/deps/yoga/YGConfig.cpp
    ./native/deps/yoga/YGEnums.cpp
    ./native/deps/yoga/YGLayout.cpp
    ./native/deps/yoga/YGNode.cpp
    ./native/deps/yoga/YGNodePrint.cpp
    ./native/deps/yoga/YGStyle.cpp
    ./native/deps/yoga/YGValue.cpp
    ./native/deps/yoga/Yoga.cpp
    ./native/deps/yoga/Event/event.cpp
    ./native/deps/yoga/internal/experiments.cpp

    ./native/core/FlexBasic/FlexBasic.cpp
    ./native/core/FlexUtils/FlexUtils.cpp
    ./native/core/YogaComp/Style.cpp
    ./native/core/YogaComp/Comp.cpp
    ./native/core/Event/EventWidget.cpp
    ./native/core/JSUtils/Event/Event.cpp
    ./native/core/JSUtils/Event/Click/Click.cpp
    ./native/core/JSUtils/Event/Input/TextChange/TextChange.cpp
    ./native/core/JSUtils/Event/Input/Focus/Focus.cpp
    ./native/core/JSUtils/variant/VariantWrap.cpp
    ./native/core/JSUtils/variant/VariantWrap.hpp

    ./native/components/Components.cpp
    ./native/components/interact/loading/Loading.cpp
    ./native/components/interact/loading/LoadingWrap.cpp
    ./native/components/mask/Mask.cpp
    ./native/components/container/Container.cpp
    ./native/components/container/ContainerWrap.cpp
    ./native/components/button/Button.cpp
    ./native/components/button/ButtonWrap.cpp
    ./native/components/view/View.cpp
    ./native/components/view/ViewWrap.cpp
    ./native/components/scrollView/ScrollView.cpp
    ./native/components/scrollView/ScrollViewWrap.cpp
    ./native/components/flexLayout/FlexLayout.cpp
    ./native/components/text/Text.cpp
    ./native/components/text/TextWrap.cpp
    ./native/components/image/Image.cpp
    ./native/components/image/ImageWrap.cpp
    ./native/components/input/Input.cpp
    ./native/components/input/InputWrap.cpp
    ./native/components/main.cpp
    ./native/render.cpp
)

# add_custom_command(OUTPUT bundle.js
#     COMMAND npm run bundle -- --outfile=./debug/bundle.js
# )

file(GLOB_RECURSE resources ${CMAKE_CURRENT_SOURCE_DIR}/*.gif )
file(COPY ${resources} DESTINATION ${CMAKE_BINARY_DIR})

# add_custom_target(jsbundle ALL DEPENDS bundle.js)

add_dependencies(render jsbundle)

include_directories(
    ${LIBUV_PATH}/include
    ${QUICKJS_PATH}
    ${RUNTIME_PATH}
    ${ENGINE_PATH}
    ./native
    ./native/components
    ./native/core
    ./native/deps
)

target_link_libraries(render
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Svg
)