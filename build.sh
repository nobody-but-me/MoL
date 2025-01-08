#!/usr/bin/env bash

# git push -f origin main

echo "[CONFIG] Do you want to run the project after this compilation? "
read -rep $"[CONFIG] (y or n): " _run


_CC=gcc
_FLAGS=-lglfw
_SOURCES=./src/*.c

# -Wno-maybe-uninitialize

time $_CC -o ./build/MoL $_SOURCES -I./include/ -I./lib/ $_FLAGS -lm -Werror -Wall -Wno-unused-variable -Wno-int-conversion

if [ $_run == "y" ]; then
    echo "[INFO] Compiled Successfully. "
    echo -e "[INFO] Running... \n"
    ./run.sh
else
    echo "[INFO] Compiled without running application. "
fi
