#!/bin/sh
find . -name 'CMakeCache.txt' -o -name 'Makefile' -o -name 'CMakeFiles' | xargs rm -rf
find . -name '*.xcodeproj' | xargs rm -rf
find . -name '*.make' | xargs rm -rf
find . -name '*.build' | xargs rm -rf