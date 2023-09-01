project(
    'FreeRTOSBuffers',
    ['c', 'cpp'],
    version: '0.1',
    default_options: [
        'c_std=gnu18',
        'cpp_std=c++17',
        'optimization=0',
        'warning_level=3',
        'debug=true',
    ],
)

# Define libraries
libraries = ['-lm', '-lc', '-lgcc', '-lnosys']

# Define macros
defines = [
    '-DCPU_MKL46Z256VLL4',
    '-DFRDM_KL46Z',
    '-DFREEDOM',
    '-DPRINTF_FLOAT_ENABLE',
    '-DSCANF_FLOAT_ENABLE',
    '-DPRINTF_ADVANCED_ENABLE',
    '-DSCANF_ADVANCED_ENABLE',
]

if get_option('buildtype').startswith('debug')
    add_project_arguments('-DDEBUG', language: ['c', 'cpp'])
endif

# Variable tracking
project_src = []
project_inc = [include_directories('include')]

# Source subdirectories
subdir('lib')
subdir('src')

# -- Project Arguments -- #
add_project_link_arguments(
    libraries,
    '--specs=nano.specs',
    '--specs=nosys.specs',
    '-fno-common',
    '-ffunction-sections',
    '-fdata-sections',
    '-ffreestanding',
    '-fno-builtin',
    '-mthumb',
    '-mapcs',
    '-Xlinker',
    '--gc-sections',
    '-Xlinker',
    '-static',
    '-Xlinker',
    '-z',
    '-Xlinker',
    'muldefs',
    '-mcpu=cortex-m0plus',
    '-mfloat-abi=soft',
    language: ['c', 'cpp'],
)

add_project_arguments(
    defines,
    '-fno-common',
    '-ffunction-sections',
    '-fdata-sections',
    '-ffreestanding',
    '-fno-builtin',
    '-mthumb',
    '-mapcs',
    '-mcpu=cortex-m0plus',
    '-mfloat-abi=soft',
    '-MMD',
    '-MP',
    language: ['c', 'cpp'],
)

add_project_arguments(
    '-fno-rtti',
    '-fno-exceptions',
    language: ['cpp'],
)

# -- Declare dependencies and libraries -- #

# Declare startup file
frdmkl46z_startup = declare_dependency(
    sources: frdmkl46z_startup_src,
    include_directories: project_inc,
    compile_args: frdmkl46z_startup_defines,
)

# Declare SDK
frdmkl46z_sdk = static_library(
    'frdmkl46z_sdk',
    frdmkl46z_sdk_src,
    c_args: ['-w', '-std=gnu99'],
    include_directories: project_inc,
    link_language: 'c',
    pic: false,
)

# Declare configuration
frdmkl46z_config = static_library(
    'frdmkl46z_config',
    frdmkl46z_config_src,
    c_args: ['-w', '-std=gnu99'],
    include_directories: project_inc,
    link_language: 'c',
    pic: false,
)

freertos = static_library(
    'freertos',
    freertos_src,
    c_args: ['-w', '-std=gnu99'],
    include_directories: project_inc,
    link_language: 'c',
    pic: false,
)

# Create the .elf file
elf = executable(
    'output',
    project_src,
    cpp_args: ['-Wno-register', '-Wno-volatile'],
    name_suffix: 'elf',
    include_directories: [project_inc],
    dependencies: [frdmkl46z_startup],
    link_with: [frdmkl46z_sdk, frdmkl46z_config, freertos],
)

# Find arm toolchain objcopy executable
objcopy = find_program('arm-none-eabi-objcopy')

# Custom target '.elf' to '.bin'
custom_target(
    'binary',
    output: '@0@.bin'.format(meson.project_name()),
    command: [
        objcopy,
        [
            '-O',
            'binary',
            elf.full_path(),
            '@0@.bin'.format(meson.project_name()),
        ],
    ],
    depends: elf,
)
