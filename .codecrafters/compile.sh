#!/bin/sh
#
# This script is used to compile your program on CodeCrafters
# 
# This runs before .codecrafters/run.sh
#
# Learn more: https://codecrafters.io/program-interface

# Exit early if any commands fail
set -e

wget https://github.com/mesonbuild/meson/releases/download/1.9.1/meson.pyz
wget https://github.com/ninja-build/ninja/releases/download/v1.13.1/ninja-linux.zip
unzip ninja-linux.zip
export PATH="$PATH:/app/"

python3 meson.pyz setup build
python3 meson.pyz compile -vC build
