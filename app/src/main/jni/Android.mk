LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

# ============================================================================#
include $(CLEAR_VARS)
LOCAL_MODULE    := libdobby
LOCAL_SRC_FILES := Dobby/$(TARGET_ARCH_ABI)/libdobby.a
include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

COMMON_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -fno-rtti -fno-exceptions -fpermissive
COMMON_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -std=c++17 -fno-rtti -fno-exceptions -fpermissive
COMMON_LDFLAGS := -Wl,--gc-sections,--strip-all, -llog
COMMON_LDLIBS := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lGLESv1_CM -lz

FILE_LIST := $(wildcard $(LOCAL_PATH)/imgui/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/xdl/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/KittyMemory/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/LAZ/IL2CppSDKGenerator/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/Struct/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/*.c*)

ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
    HOOK_SRC := $(wildcard $(LOCAL_PATH)/include/And64InlineHook/*.c*)
else
    HOOK_SRC := $(wildcard $(LOCAL_PATH)/include/Substrate/*.c*)
endif

# Exclusively build lunar (libPrabirxLive.so)
include $(CLEAR_VARS)
LOCAL_MODULE           := lion
LOCAL_CFLAGS           := $(COMMON_CFLAGS)
LOCAL_CPPFLAGS         := $(COMMON_CPPFLAGS)
LOCAL_LDFLAGS          := $(COMMON_LDFLAGS)
LOCAL_LDLIBS           := $(COMMON_LDLIBS)
LOCAL_C_INCLUDES       := $(LOCAL_PATH) $(LOCAL_PATH)/include $(LOCAL_PATH)/Dobby $(LOCAL_PATH)/imgui $(LOCAL_PATH)/KittyMemory $(LOCAL_PATH)/Unity $(LOCAL_PATH)/include/And64InlineHook $(LOCAL_PATH)/include/Substrate
LOCAL_SRC_FILES        := $(FILE_LIST:$(LOCAL_PATH)/%=%) $(HOOK_SRC:$(LOCAL_PATH)/%=%)
LOCAL_STATIC_LIBRARIES := libdobby
LOCAL_CPP_FEATURES     := exceptions
include $(BUILD_SHARED_LIBRARY)
