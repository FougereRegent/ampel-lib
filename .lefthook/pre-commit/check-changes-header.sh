#!/bin/bash

major="MAJOR"
minor="MINOR"
build="BUILD"

file="./ampel-lib.h"

nbCorrelation=$(cat ./ampel-lib.h | grep -Ei "X_($major|$minor|$build)" | wc -w)
if [[ $((nbCorrelation)) -gt 0 ]]; then
  sed "/^#define LIBLED_VERSION_MAJOR/c\#define LIBLED_VERSION_MAJOR X_MAJOR" -i $file
  sed "/^#define LIBLED_VERSION_MINOR/c\#define LIBLED_VERSION_MINOR X_MINOR" -i $file
  sed "/^#define LIBLED_VERSION_BUILD/c\#define LIBLED_VERSION_BUILD X_BUILD" -i $file
fi
