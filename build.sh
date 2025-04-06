
#!/usr/bin/env bash

# git commit -am "<message>"
# git push -f origin main

# echo "[CONFIG] Do you want to run the project after this compilation? "
# read -rep $"[CONFIG] (y or n): " _run

_CC=gcc
_FLAGS=(-lglfw -lm -Wall -std=c11 -Wno-int-conversion -Wno-unused-result -Wno-unused-parameter -Wno-stringop-overflow)
_SOURCES=./src/*.c

compile() {
    time $_CC -o ./build/MoL $_SOURCES -I./include/ -I./lib/ ${_FLAGS[*]}
}

if [ $1 == "--c" ]; then
    echo -e "[INFO] Compiling only... \n"
    compile;
elif [ $1 == "--r" ]; then
    echo -e "[INFO] Running... \n"
    ./run.sh
elif [ $1 == "--b" ]; then
    compile;
    echo "[INFO] Compiled Successfully. "
    echo -e "[INFO] Running... \n"
    ./run.sh;
else
    echo "[INFO] No flag given. "
    exit 1
fi
