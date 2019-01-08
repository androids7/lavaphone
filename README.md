# lavaphone
基于安卓的新lava客户端


include $(CLEAR_VARS)  
LOCAL_MODULE := core2
LOCAL_SRC_FILES += ../obj/local/$(TARGET_ARCH_ABI)/libcore.so
#LOCAL_SRC_FILES := ../../sojni/libs/armeabi/libinit.so  
include $(PREBUILT_SHARED_LIBRARY)



include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := lavatest
LOCAL_SRC_FILES := main.c


#LOCAL_LDLIBS= core2
ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_CFLAGS += -ffast-math -mtune=atom -mssse3 -mfpmath=sse
endif

LOCAL_SHARED_LIBRARIES += core
include $(BUILD_SHARED_LIBRARY)

