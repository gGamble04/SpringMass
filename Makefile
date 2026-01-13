CC ?= gcc
KEEP_TEMPS ?= 0

BIN := springmass

SRC := \
	src/sim/main.c \
	src/sim/sim.c \
	src/core/physics.c \
	src/renderer/renderer.c \
	src/renderer/graph.c \
	src/UI/ui.c

OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

CPPFLAGS := -Isrc -I../raylib/examples/core
CFLAGS ?= -std=c11 -O2

ifeq ($(KEEP_TEMPS),1)
    CFLAGS += -save-temps=obj
endif

LDLIBS := -lraylib -lm -ldl -lpthread -lrt -lX11

.PHONY: all strict debug package clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

strict: clean
	$(MAKE) all CFLAGS='-std=c11 -O2 -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-result'

debug: clean
	$(MAKE) all CFLAGS='-std=c11 -O0 -g -Wall -Wextra'

package:
	./scripts/package.sh

clean:
ifeq ($(KEEP_TEMPS),0)
	rm -rf build $(BIN)
else
	@echo "Keeping temporary files (KEEP_TEMPS=$(KEEP_TEMPS))"
	rm -f $(BIN)
	find build -type f \( -name '*.i' -o -name '*.s' -o -name '*.ii' \) -delete
endif