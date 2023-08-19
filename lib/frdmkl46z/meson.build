# Linker file
if meson.get_external_property('ramlinker')
    linker_file = files('device/gcc/MKL46Z256xxx4_ram.ld')
else
    linker_file = files('device/gcc/MKL46Z256xxx4_flash.ld')
endif


# Include files
project_inc += [
    include_directories('CMSIS/Include'),
    include_directories('device/.'),
    include_directories('device/drivers'),
    include_directories('device/utilities/io'),
    include_directories('device/utilities/str'),
    include_directories('device/utilities/log'),
    include_directories('device/utilities'),
]

# Add linker file
add_project_link_arguments(
    '-T@0@/@1@'.format(meson.project_source_root(), linker_file[0]),
    '-static',
    language: ['c', 'cpp'],
)

# Startup file
frdmkl46z_startup_src = files('device/gcc/startup_MKL46Z4.S')

# Project SDK files
frdmkl46z_sdk_src = [
    files('device/system_MKL46Z4.c'),
    files('device/system_MKL46Z4.h'),
    files('device/drivers/fsl_clock.h'),
    files('device/drivers/fsl_clock.c'),
    files('device/drivers/fsl_ftfx_adapter.h'),
    files('device/drivers/fsl_ftfx_utilities.h'),
    files('device/drivers/fsl_ftfx_features.h'),
    files('device/drivers/fsl_ftfx_controller.c'),
    files('device/drivers/fsl_ftfx_controller.h'),
    files('device/drivers/fsl_ftfx_flash.c'),
    files('device/drivers/fsl_ftfx_flash.h'),
    files('device/drivers/fsl_ftfx_cache.c'),
    files('device/drivers/fsl_ftfx_cache.h'),
    files('device/drivers/fsl_ftfx_flexnvm.c'),
    files('device/drivers/fsl_ftfx_flexnvm.h'),
    files('device/drivers/fsl_flash.h'),
    files('device/drivers/fsl_common.h'),
    files('device/drivers/fsl_common.c'),
    files('device/drivers/fsl_lpsci.h'),
    files('device/drivers/fsl_lpsci.c'),
    files('device/drivers/fsl_uart.h'),
    files('device/drivers/fsl_uart.c'),
    files('device/drivers/fsl_port.h'),
    files('device/drivers/fsl_smc.h'),
    files('device/drivers/fsl_smc.c'),
    files('device/drivers/fsl_gpio.h'),
    files('device/drivers/fsl_gpio.c'),
    files('device/utilities/io/fsl_io.c'),
    files('device/utilities/io/fsl_io.h'),
    files('device/utilities/log/fsl_log.c'),
    files('device/utilities/log/fsl_log.h'),
    files('device/utilities/str/fsl_str.c'),
    files('device/utilities/str/fsl_str.h'),
    files('device/utilities/fsl_debug_console.c'),
    files('device/utilities/fsl_debug_console.h'),
    files('device/utilities/fsl_debug_console_conf.h'),
    files('device/utilities/fsl_assert.c'),
]
