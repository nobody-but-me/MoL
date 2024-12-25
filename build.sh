#!/usr/bin/env bash

echo "[CONFIG] Do you want to run the project after this compilateion? "
read -rep $"[CONFIG] (y or n): " _run


_CC=gcc
_FLAGS=-lglfw
_SOURCES=./src/*.c

$_CC -o ./build/MoL $_SOURCES -I./include/ $_FLAGS -Werror -Wall -Wno-unused-variable -Wno-maybe-uninitialized

if [ $_run == "y" ]; then
    echo "[INFO] Compiled Successfully. "
    echo -e "[INFO] Running... \n"
    ./run.sh
else
    echo "[INFO] Compiled without running application. "
fi
