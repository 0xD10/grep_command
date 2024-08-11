#!/usr/bin/sh
cmake -S . -B ./build
make -C ./build/
mv ./build/program/grep .
rm -rf ./build
