# ⚙️ FRDM-KL46Z (Meson and CMSIS-DAP toolchain)
Development environment and tools for working with the FRDM-KL46Z microcontroller board using the Meson build system and the CMSIS-DAP interface firmware

## 📀 Makefile
Provided _Makefile_ easies compilation by reducing the ammount of commands required for compiling and uploading the code, the provided commands are:

* __setup__ Setup meson project
* __build__ Compile _.elf_ file
* __build_binary__ Compile _.bin_ file for manual upload
* __set_debug__ Set DEBUG flags (default)
* __set_release__ Set RELEASE flags
* __upload__ Compile and upload the code using _OpenOCD_ (Requires [OpenOCD and CMSIS-DAP](#resources))

## 🏗️ Building with Meson
Compilation is done with ___arm-none-eabi-gcc___ toolchain
1. Setup project with ```meson setup --cross-file cross-compilation.toml build```
2. Compile the project with ```meson compile -C build```

The output will be found in _'build/output.elf'_

### Other targets:
Are called with ```meson compile -C build <target>```

* __binary__ Create a _.bin_ file from _.elf_ file for manual upload, copy and paste this file into the device drive.
	

## Resources
* [OpenOCD Debugger](https://openocd.org/)
* [CMSIS-DAP Interface Firmware](https://os.mbed.com/handbook/Firmware-FRDM-KL46Z)

## 🐞 Debugging
Easiest way of debugging is via [OpenOCD](#resources) which requires [CMSIS-DAP Interface Firmware](#resources) to be installed.

1. Start the __OpenOCD__ server with:
```
openocd -f board/frdm-kl46z.cfg
```
2. Connect the __GDB Debugger__ with
```
gdb build/output.elf -ex "target extended-remote localhost:3333"
```