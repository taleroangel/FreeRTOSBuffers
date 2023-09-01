# -- Include FreeRTOS -- #
subdir('freertos')

# -- Compile CMSIS -- #
project_inc += [
    include_directories('CMSIS/Include'),
]

# -- Compile board SDK -- #

# Linker file
if meson.get_external_property('ramlinker')
    linker_file = files('devices/MKL46Z4/gcc/MKL46Z256xxx4_ram.ld')
else
    linker_file = files('devices/MKL46Z4/gcc/MKL46Z256xxx4_flash.ld')
endif

# Include files
project_inc += [
    include_directories('devices/MKL46Z4'),
    include_directories('devices/MKL46Z4/drivers'),
    include_directories('devices/MKL46Z4/utilities/io'),
    include_directories('devices/MKL46Z4/utilities/str'),
    include_directories('devices/MKL46Z4/utilities/log'),
    include_directories('devices/MKL46Z4/utilities'),
]

# Add linker file
add_project_link_arguments(
    '-T@0@/@1@'.format(meson.project_source_root(), linker_file[0]),
    '-static',
    language: ['c', 'cpp'],
)

# Startup file
frdmkl46z_startup_src = files('devices/MKL46Z4/gcc/startup_MKL46Z4.S')
frdmkl46z_startup_defines = ['-D__STARTUP_CLEAR_BSS']

# Project SDK files
frdmkl46z_sdk_src = [
    files('devices/MKL46Z4/drivers/fsl_clock.h'),
    files('devices/MKL46Z4/drivers/fsl_clock.c'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_adapter.h'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_utilities.h'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_features.h'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_controller.c'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_controller.h'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_flash.c'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_flash.h'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_cache.c'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_cache.h'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_flexnvm.c'),
    files('devices/MKL46Z4/drivers/fsl_ftfx_flexnvm.h'),
    files('devices/MKL46Z4/drivers/fsl_flash.h'),
    files('devices/MKL46Z4/drivers/fsl_common.h'),
    files('devices/MKL46Z4/drivers/fsl_common.c'),
    files('devices/MKL46Z4/system_MKL46Z4.c'),
    files('devices/MKL46Z4/system_MKL46Z4.h'),
    files('devices/MKL46Z4/drivers/fsl_lpsci.h'),
    files('devices/MKL46Z4/drivers/fsl_lpsci.c'),
    files('devices/MKL46Z4/drivers/fsl_uart.h'),
    files('devices/MKL46Z4/drivers/fsl_uart.c'),
    files('devices/MKL46Z4/drivers/fsl_port.h'),
    files('devices/MKL46Z4/drivers/fsl_smc.h'),
    files('devices/MKL46Z4/drivers/fsl_smc.c'),
    files('devices/MKL46Z4/utilities/io/fsl_io.c'),
    files('devices/MKL46Z4/utilities/io/fsl_io.h'),
    files('devices/MKL46Z4/utilities/log/fsl_log.c'),
    files('devices/MKL46Z4/utilities/log/fsl_log.h'),
    files('devices/MKL46Z4/utilities/str/fsl_str.c'),
    files('devices/MKL46Z4/utilities/str/fsl_str.h'),
    files('devices/MKL46Z4/utilities/fsl_debug_console.c'),
    files('devices/MKL46Z4/utilities/fsl_debug_console.h'),
    files('devices/MKL46Z4/utilities/fsl_debug_console_conf.h'),
    files('devices/MKL46Z4/drivers/fsl_gpio.h'),
    files('devices/MKL46Z4/drivers/fsl_gpio.c'),
    files('devices/MKL46Z4/utilities/fsl_assert.c'),
]

# -- Fetch board configuration -- #
project_inc += include_directories('config')
frdmkl46z_config_src = [
    files('config/pin_mux.c'),
    files('config/clock_config.c'),
    files('config/board.c'),
]
