cmake_minimum_required(VERSION 3.4.1)

add_library(hello-jni SHARED
            hello-jni.c)

add_library(DBase SHARED IMPORTED)
set_target_properties(DBase
                        PROPERTIES IMPORTED_LOCATION
                        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libDBase.so)

# Include libraries needed for hello-jni lib
target_link_libraries(hello-jni
                      android
                      log
                      DBase)
