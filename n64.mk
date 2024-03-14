BUILD_DIR=build
GAME=pinball
include $(N64_INST)/include/n64.mk

N64_C_AND_CXX_FLAGS += -ISpaceCadetPinball -Wno-error -DLIBDRAGON_FAST_MATH
N64_CXXFLAGS += -fno-exceptions -fno-threadsafe-statics

src = $(wildcard SpaceCadetPinball/*.cpp)
assets_wav = $(shell find assets -name '*.WAV')
assets_dat = $(wildcard assets/*.DAT)

assets_conv = $(patsubst %.WAV,%.wav64,$(patsubst assets/%,filesystem/%,$(assets_wav))) \
              $(addprefix filesystem/,$(notdir $(assets_dat))) \
						  filesystem/PB_MSGFT.bin

AUDIOCONV_FLAGS ?= --wav-compress 0

all: $(GAME).z64

filesystem/%.DAT: assets/%.DAT
	@mkdir -p $(dir $@)
	@echo "    [CP] $@"
	@cp $< $@

filesystem/PB_MSGFT.bin: SpaceCadetPinball/PB_MSGFT.bin
	@mkdir -p $(dir $@)
	@echo "    [CP] $@"
	@cp $< $@

filesystem/%.wav64: assets/%.WAV
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $@ $<

$(BUILD_DIR)/$(GAME).dfs: $(assets_conv)
	$(N64_MKDFS) $@ filesystem/

$(BUILD_DIR)/$(GAME).elf: $(src:%.c=$(BUILD_DIR)/%.o) $(src:%.cpp=$(BUILD_DIR)/%.o)

$(GAME).z64: N64_ROM_TITLE="Pinball"

$(GAME).z64: $(BUILD_DIR)/$(GAME).dfs

clean:
	@rm -rf $(BUILD_DIR)/* $(GAME).z64

-include $(wildcard $(BUILD_DIR)/SpaceCadetPinball/*.d)

.PHONY: all clean $(TARGET)
