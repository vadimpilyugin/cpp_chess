#!/bin/bash
set -o errexit

mkdir -p bin
for i in $(ls *.cpp)
do
	g++ -std=c++11 -o bin/$i.o -c $i
done
