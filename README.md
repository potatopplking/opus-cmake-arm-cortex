# opus-cmake-arm-cortex

*OPUS for ARM Cortex made simple*

Forked from eppixx [opus-cmake](https://github.com/eppixx/opus-cmake) repo, using updated version by [bjorn-oivind](https://github.com/bjorn-oivind/opus-cmake) and adapted for ARM Cortex-M4. Porting, compiling and usage instructions are given below. Instructions for STM32CubeIDE are also presented.

## Porting

### Porting to different MCU family/type

Current configuration is specific for STM32L4R9xx (ARM Cortex-M4, hard FPU). To adapt for other ARM Cortex, change compile flags in [CMakeLists.txt](CMakeLists.txt), specifically:

* `-mcpu=cortex-m4` : defines Cortex family
* `-DSTM32L4R9xx` : defines macro with MCU type, this is used in STM32 HAL libraries
* `-mfpu=fpv4-sp-d16 -mfloat-abi=hard` specifies type of hardware FPU

If unsure, try omitting some or all of the above.

### Using static allocation instead of malloc()

In this configuration dynamic memory allocation is disabled. In OPUS, this is done as follows:

From [documentation](https://wiki.xiph.org/OpusFAQ#I_can.27t_use_malloc_or_much_stack_on_my_embedded_platform._How_do_I_make_Opus_work.3F): compile with `CFLAGS="-DOVERRIDE_OPUS_ALLOC -DOVERRIDE_OPUS_FREE -D'opus_alloc(x)=NULL' -D'opus_free(x)=NULL' "`.

Then use _init() functions instad of _create() (e.g. for encoder).

If you want to enable dynamic OPUS context allocation, simply delete/comment out this part from CMakeLists.txt.

## Compiling

```bash
mkdir build_arm-none-eabi
cd build_arm-none-eabi
cmake ..
make
```

Which should give you `libopus.a` static library.

## Usage

### Generic

Include opus header files and link the static library.

### STM32CubeIDE

## Notes

## Decreasing complexity / CPU time:

From [documentation](https://wiki.xiph.org/OpusFAQ#I_can.27t_use_malloc_or_much_stack_on_my_embedded_platform._How_do_I_make_Opus_work.3F):

- enable hardfpu, if present on device
- use fixed-point floats
- decrease decrease complexity (OPUS_SET_COMPLEXITY)
  
Size of opus library can be decreased by:

- stripping debug symbols

## Compiling for x86 linux

Enable dynamic allocation (see above), remove `CPU_ARM` option and C flags for ARM. Then follow compilation instructions above.