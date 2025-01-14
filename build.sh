# !/bin/bash

if [ "$1" = "clean" ]; then
	echo "clean......"
	rm -rf build/*
else
	# cmake 构建
	cmake -B build -S .
	# cmake 编译
	cmake --build build
fi
