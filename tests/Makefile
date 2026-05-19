ROOT := $(abspath $(CURDIR)/..)
BUILD_DIR ?= /tmp/x-cube-ble1-tests
TARGET := $(BUILD_DIR)/test_ble_modules

CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O0 --coverage
INCLUDES := \
	-I$(ROOT)/tests/stubs \
	-I$(ROOT)/Middlewares/ST/BlueNRG-MS/utils \
	-I$(ROOT)/Middlewares/ST/BlueNRG-MS/includes

SOURCES := \
	$(ROOT)/tests/test_ble_modules.c \
	$(ROOT)/tests/stubs/mock_irq.c \
	$(ROOT)/Middlewares/ST/BlueNRG-MS/utils/ble_list.c \
	$(ROOT)/Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_utils_small.c

.PHONY: all run coverage clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $@

run: $(TARGET)
	$(TARGET)

coverage: run
	cd $(BUILD_DIR) && gcov \
		./test_ble_modules-ble_list.gcno \
		./test_ble_modules-bluenrg_utils_small.gcno

clean:
	rm -rf $(BUILD_DIR)
