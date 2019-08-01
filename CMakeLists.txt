# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.2)
project(esp8266-web-fastled-music)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_BUILD_VERBOSE ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --verbose
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_MONITOR ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion device monitor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_TEST ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_REBUILD_PROJECT_INDEX ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion init --ide clion
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${SRC_LIST} src/Application.cpp src/Application.h src/config/config.h src/adc/ExternalADC.cpp src/adc/ExternalADC.h src/led/Led.cpp src/led/Led.h src/led/animations/LedAnimation.cpp src/led/animations/LedAnimation.h src/led/animations/StrobeAnimation.cpp src/led/animations/StrobeAnimation.h src/led/animations/NoopAnimation.cpp src/led/animations/NoopAnimation.h src/led/AnimationFactory.cpp src/led/AnimationFactory.h src/web/actions/SetAnimationAction.cpp src/web/actions/SetAnimationAction.h src/led/animations/SimpleFrequencyAnimation.cpp src/led/animations/SimpleFrequencyAnimation.h src/led/animations/FrequencyAnimation.cpp src/led/animations/FrequencyAnimation.h src/web/actions/AdcAction.cpp src/web/actions/AdcAction.h src/led/animations/FrequencyStrobeAnimation.cpp src/led/animations/FrequencyStrobeAnimation.h src/led/animations/RunningFrequencyAnimation.cpp src/led/animations/RunningFrequencyAnimation.h src/led/animations/SpectrumAnalyzerFrequencyAnimation.cpp src/led/animations/SpectrumAnalyzerFrequencyAnimation.h src/led/animations/RainbowAnimation.cpp src/led/animations/RainbowAnimation.h src/led/animations/DirectColorAnimation.cpp src/led/animations/DirectColorAnimation.h src/led/animations/DynamicColorAnimation.cpp src/led/animations/DynamicColorAnimation.h src/led/animations/DotBeatAnimation.cpp src/led/animations/DotBeatAnimation.h src/led/animations/BlendwaveAnimation.cpp src/led/animations/BlendwaveAnimation.h src/led/animations/BlurAnimation.cpp src/led/animations/BlurAnimation.h src/led/animations/ConfettiAnimation.cpp src/led/animations/ConfettiAnimation.h)
