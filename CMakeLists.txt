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
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --environment nodemcuv2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_BUILD_VERBOSE ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --verbose --environment nodemcuv2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload --environment nodemcuv2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_UPLOAD_OTA ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload --environment nodemcuv2ota
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
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs --environment nodemcuv2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        PLATFORMIO_UPLOADFS_OTA ALL
        COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs --environment nodemcuv2ota
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

add_executable(${PROJECT_NAME} ${SRC_LIST} src/Application.cpp src/Application.h src/config/config.h src/adc/ExternalADC.cpp src/adc/ExternalADC.h src/led/Led.cpp src/led/Led.h src/led/animations/LedAnimation.cpp src/led/animations/LedAnimation.h src/led/animations/static/StrobeAnimation.cpp src/led/animations/static/StrobeAnimation.h src/led/animations/NoopAnimation.cpp src/led/animations/NoopAnimation.h src/led/AnimationFactory.cpp src/led/AnimationFactory.h src/web/actions/SetAnimationAction.cpp src/web/actions/SetAnimationAction.h src/led/animations/frequency/SimpleFrequencyAnimation.cpp src/led/animations/frequency/SimpleFrequencyAnimation.h src/led/animations/MusicAnimation.cpp src/led/animations/MusicAnimation.h src/web/actions/AdcAction.cpp src/web/actions/AdcAction.h src/led/animations/frequency/FrequencyStrobeAnimation.cpp src/led/animations/frequency/FrequencyStrobeAnimation.h src/led/animations/frequency/RunningFrequencyAnimation.cpp src/led/animations/frequency/RunningFrequencyAnimation.h src/led/animations/frequency/SpectrumAnalyzerFrequencyAnimation.cpp src/led/animations/frequency/SpectrumAnalyzerFrequencyAnimation.h src/led/animations/static/RainbowAnimation.cpp src/led/animations/static/RainbowAnimation.h src/led/animations/static/DirectColorAnimation.cpp src/led/animations/static/DirectColorAnimation.h src/led/animations/static/DynamicColorAnimation.cpp src/led/animations/static/DynamicColorAnimation.h src/led/animations/static/DotBeatAnimation.cpp src/led/animations/static/DotBeatAnimation.h src/led/animations/static/BlendwaveAnimation.cpp src/led/animations/static/BlendwaveAnimation.h src/led/animations/static/BlurAnimation.cpp src/led/animations/static/BlurAnimation.h src/led/animations/static/ConfettiAnimation.cpp src/led/animations/static/ConfettiAnimation.h src/web/actions/WiFiSetAction.cpp src/web/actions/WiFiSetAction.h src/web/actions/WiFiResetAction.cpp src/web/actions/WiFiResetAction.h src/web/actions/WiFiScanAction.cpp src/web/actions/WiFiScanAction.h src/wifi/WiFiManager.cpp src/wifi/WiFiManager.h src/storage/SettingsStorage.cpp src/storage/SettingsStorage.h src/led/animations/ConfigurableLedAnimation.hpp src/web/actions/PutSettingsAction.cpp src/web/actions/PutSettingsAction.h src/web/actions/GetSettingsAction.cpp src/web/actions/GetSettingsAction.h src/web/actions/DeleteSettingsAction.cpp src/web/actions/DeleteSettingsAction.h src/led/animations/uv/UvMeterAnimation.cpp src/led/animations/uv/UvMeterAnimation.h src/web/events/SocketEventHandler.cpp src/web/events/SocketEventHandler.h)
