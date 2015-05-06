#
# Copyright (c) 2011 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../../../..

# Target CPU architecture: cortex-m3, cortex-m4
ARCH = cortex-m3

# Target part: none, sam3n4 or sam4l4aa
PART = none

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET_FLASH = awp.elf
# TARGET_SRAM = getting-started_sram.elf

BUILD_DIR = Output

#FileList Macros
ECHO=echo
BUILDVERBOSITY = @$(ECHO) $(notdir $@);
GENPREFIX        = .
INC_DIR = ../../../project/includes
FILELIST_MK = ../filelist.mk
PRINTF = printf
RM = rm -f
ROOT = ../../..


include $(FILELIST_MK)

# List of assembler source files.
ASSRCS = InitialPlatform/scrs/hwal/McuDrv/startup/startup_stm32f10x_md_freertos.S

# List of include paths.
INC_PATH = InitialPlatform/project/includes               

# Additional search paths for libraries.
LIB_PATH =  \
#       project/builder/Lib/GCC\
#       sources/bsw/SrvL/SysSrv/Os/_gen

# List of libraries to use during linking.
LIBS =  

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT_FLASH = InitialPlatform/project/builder/linker/STM32F103-MD.ld
LINKER_SCRIPT_SRAM  = 

# Path relative to top level directory pointing to a linker script.
DEBUG_SCRIPT_FLASH = 
DEBUG_SCRIPT_SRAM  = 

# Project type parameter: all, sram or flash
PROJECT_TYPE        = flash

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -O1

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = 

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
	-D STM32F10X_MD_VL         \
	-D USE_STDPERIPH_DRIVER    \
	-D HSE_VALUE=8000000
       # -D ARM_MATH_CM3=true                               \
       # -D BOARD=SAM3N_EK                                  \
       # -D __SAM3N4C__                                     \
       # -D printf=iprintf                                  \
       # -D scanf=iscanf

# Extra flags to use when linking
LDFLAGS = \

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 
