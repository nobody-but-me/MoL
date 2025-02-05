
#!/usr/bin/env bash

# git 
# git push -f origin main

# echo "[CONFIG] Do you want to run the project after this compilation? "
# read -rep $"[CONFIG] (y or n): " _run

_CC=gcc
_FLAGS=(-lglfw)
_SOURCES=./src/*.c

compile() {
    time $_CC -o ./build/MoL $_SOURCES -I./include/ -I./lib/ ${_FLAGS[*]} -lm -Werror -Wall -Wno-unused-variable -Wno-int-conversion
}

if [ $1 == "--c" ]; then
    echo -e "[INFO] Compiling only... \n"
    compile;
elif [ $1 == "--r" ]; then
    echo -e "[INFO] Running... \n"
    ./run.sh
elif [ $1 == "--cr" ]; then
    compile;
    echo "[INFO] Compiled Successfully. "
    echo -e "[INFO] Running... \n"
    ./run.sh;
else
    echo "[INFO] No flag given. "
    exit 1
fi
