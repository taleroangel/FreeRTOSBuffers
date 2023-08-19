# Executables location
MESON	=	meson
OPENOCD	=	openocd
# Files location
ELF_FILE =	build/output.elf

all: build

# Meson project setup
build/build.ninja:
	$(MESON) setup --cross-file cross-compilation.toml build
.PHONY: setup
setup: build/build.ninja

# Build the .elf file
.PHONY: build
build: setup
	$(MESON) compile -C build

# Build the .bin file
.PHONY: build_binary
build_binary:
	$(MESON) compile -C build binary

# Change to DEBUG settings (Default)
.PHONY: set_debug
set_debug:
	$(MESON) configure --buildtype=debug --optimization=0 -Db_lto=false -Db_ndebug=false build

# Change to RELEASE settings
.PHONY: set_release
set_release:
	$(MESON) configure --buildtype=release --optimization=s -Db_lto=true -Db_ndebug=true build

# Upload program using OpenOCD
.PHONY: upload
upload: build
	$(OPENOCD) -f board/frdm-kl46z.cfg -c "program $(ELF_FILE) verify reset exit"

# Clean the 'build' folder
.PHONY: clean
clean:
	rm -rf build