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
  curl --output $cache_path https://mirrors.cloud.tencent.com/homebrew-bottles/gmp-6.2.1_1.arm64_big_sur.bottle.tar.gz
  # parsed=($response)
  ./arm-homebrew/bin/brew install $cache_path
fi
