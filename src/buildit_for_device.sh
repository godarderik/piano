#!/bin/bash

if [ ! "$PalmPDK" ];then
PalmPDK=/opt/PalmPDK
fi

###################################
### List your source files here ###
### SRC="<source1> <source2>"  ###
###################################
SRC="key.hpp key.cpp piano.cpp  "

###################################
### Name your output executable ###
### OUTFILE="<executable-name>"###
###################################
OUTFILE="piano"


###################################
######## Do not edit below ########
###################################
PATH=$PATH:${PalmPDK}/arm-gcc/bin

CC="arm-none-linux-gnueabi-gcc"

SYSROOT="${PalmPDK}/arm-gcc/sysroot"

INCLUDEDIR="${PalmPDK}/include"
LIBDIR="${PalmPDK}/device/lib"
CPPFLAGS="-I${INCLUDEDIR} -I${INCLUDEDIR}/SDL --sysroot=$SYSROOT"
LDFLAGS="-L${LIBDIR} -Wl,--allow-shlib-undefined -s"
LIBS="-lSDL -lGLES_CM -lpdl -lsdl_mixer -lsdl_image"
###################################

if [ "$SRC" == "" ];then
	echo "Source files not specified. Please edit the SRC variable inside this script."
	exit 1
fi

if [ "$OUTFILE" == "" ];then
	echo "Output file name not specified. Please edit the OUTFILE variable inside this script."
	exit 1
fi

$CC -mcpu=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp $CPPFLAGS $LDFLAGS $LIBS -o $OUTFILE $SRC

