#!/bin/bash

# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

set -ex

if [ "$CIBW_ARCHS_MACOS" = "arm64" ]; then
  mkdir arm-homebrew
  curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C arm-homebrew
  cache_path=$(./arm-homebrew/bin/brew --cache gmp)
  echo $cache_path
  curl --output $cache_path http://ftp.swin.edu.au/gnu/gmp/gmp-6.2.1.tar.xz
  # parsed=($response)
  ./arm-homebrew/bin/brew install gmp
fi
