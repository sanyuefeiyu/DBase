# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := DBase

LOCAL_SRC_FILES += ../../../src/common/DFile.cpp
LOCAL_SRC_FILES += ../../../src/common/DLog.cpp
LOCAL_SRC_FILES += ../../../src/common/android/DLogAndroid.cpp
LOCAL_SRC_FILES += ../../../src/common/android/DTimeAndroid.cpp
LOCAL_SRC_FILES += ../../../src/common/android/DLoadAndroid.c
LOCAL_SRC_FILES += ../../../src/common/android/DMiscAndroid.c
LOCAL_SRC_FILES += ../../../src/alogrithm/base64/DBase64.cpp
LOCAL_SRC_FILES += ../../../src/alogrithm/safty/md5/DMD5.c
LOCAL_SRC_FILES += ../../../src/alogrithm/safty/md5/cifs/cifs_block.c
LOCAL_SRC_FILES += ../../../src/alogrithm/safty/md5/cifs/md5.c

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../src/common

# for logging
LOCAL_LDLIBS    += -L$(LOCAL_PATH)/libs/ -llog

include $(BUILD_SHARED_LIBRARY)
