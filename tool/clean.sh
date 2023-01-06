#!/bin/sh
find . -name 'CMakeCache.txt' -o -name 'Makefile' -o -name 'CMakeFiles' | xargs rm -rf
find . -name '*.xcodeproj' | xargs rm -rf
find . -name '*.make' | xargs rm -rf
find . -name '*.build' | xargs rm -rf
find ./build/XCBuildData -name '*.build' | xargs rm -rf
find ./build/XCBuildData -name '*.xcbuild' | xargs rm -rf
find ./build/XCBuildData -name '*.json' | xargs rm -rf
find ./build/XCBuildData -name '*.txt' | xargs rm -rf
find ./build/XCBuildData -name '*.db' | xargs rm -rf
/usr/bin/find . -type d -empty -delete