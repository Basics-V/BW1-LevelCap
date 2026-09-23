PROJECT  := LevelCap
ROM_CODE ?= IRBO

vfs_dir   := src
ovl_dir   := $(vfs_dir)/overlay
incl_dir  := include
link_dir  := linker
build_dir := build
obj_dir   := $(build_dir)/code
ld_dir    := $(build_dir)/link

srcs = $(wildcard $(vfs_dir)/*.c) $(wildcard $(ovl_dir)/*.c)
objs = $(addprefix $(obj_dir)/, $(notdir $(srcs:.c=.o)))
hdrs = $(wildcard $(incl_dir)/*.h) $(wildcard $(incl_dir)/overlay/*.h)
ld_ins  := $(wildcard $(link_dir)/*.ld.in)
ld_outs := $(addprefix $(ld_dir)/, $(notdir $(ld_ins:.ld.in=.ld)))

target = $(build_dir)/$(ROM_CODE)_$(PROJECT).elf

cpp     := arm-none-eabi-cpp
gcc     := arm-none-eabi-gcc
ld      := arm-none-eabi-ld
objdump := arm-none-eabi-objdump

c_flags     = -D$(ROM_CODE) -mthumb -march=armv5t -nostdlib -O2 $(addprefix -I, $(dir $(hdrs)))
ld_in_flags = -D$(ROM_CODE) -D__LINKER__ -P -x c -E $(addprefix -I, $(dir $(hdrs)))
ld_flags    = $(addprefix -T, $(ld_outs))

vpath %.c     $(vfs_dir)
vpath %.c     $(ovl_dir)
vpath %.ld.in $(link_dir)

all: $(target)
IRBO IRBI IRAI:
	@ $(MAKE) clean
	@ $(MAKE) ROM_CODE=$@

$(target): $(objs) $(ld_outs)
	@ echo "[+] Linking all objects into $@..."
	@ $(ld) $(ld_flags) -o $@ $<

$(ld_dir)/%.ld: %.ld.in
	@ echo "[+] Processing linker scripts..."
	@ mkdir -p $(@D)
	@ $(cpp) $(ld_in_flags) $< -o $@

$(obj_dir)/%.o: %.c $(hdrs)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@

verify:
	@ $(eval TARGET := $(firstword $(wildcard $(build_dir)/*.elf)))
	@ $(eval ROM_CODE := $(firstword $(subst _, ,$(notdir $(TARGET)))))
	@ echo "[?] Verifying build $(ROM_CODE)..."
	@ $(objdump) -d $(target)

clean:
	rm -rf $(build_dir)

.PHONY: all verify clean IRBO IRBI IRAI
