#!/bin/bash

make -p build
BUILDDIR=build HOSTFILE=./etc/linux.c make all -B
