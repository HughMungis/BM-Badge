SDK_TARGET ?= $(PRJ_ROOT)/output/libnordic-shim.a
SRC_ROOT := $(PRJ_ROOT)

SDK_SRCS := $(wildcard $(PRJ_ROOT)/shim/*.c)
SDK_SRCS += $(wildcard $(PRJ_ROOT)/shim/*.cpp)
SDK_SRCS += $(wildcard $(PRJ_ROOT)/shim/*.S)

SDK_INCLUDES := -I$(PRJ_ROOT)/shim \
	-I$(PRJ_ROOT)/.. \
	-I$(PRJ_ROOT)/../src \
	-I$(PRJ_ROOT)/../src/modules/cmixer \
	-I$(PRJ_ROOT)/../src/engine \
	$(shell pkg-config --cflags-only-I sdl2) \
	-I/usr/include

TOOLCHAIN = ""