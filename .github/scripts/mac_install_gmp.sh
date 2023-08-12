#!/bin/bash

# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

set -ex

if [ "$CIBW_ARCHS_MACOS" = "arm64" ]; then
  mkdir arm-homebrew
  curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C arm-homebrew
  cache_path=$(./arm-homebrew/bin/brew --cache --build-from-source gmp)
  echo $cache_path
  curl --output $cache_path https://src.fedoraproject.org/repo/pkgs/gmp/gmp-6.2.1.tar.xz/sha512/c99be0950a1d05a0297d65641dd35b75b74466f7bf03c9e8a99895a3b2f9a0856cd17887738fa51cf7499781b65c049769271cbcb77d057d2e9f1ec52e07dd84/gmp-6.2.1.tar.xz
  # parsed=($response)
  ./arm-homebrew/bin/brew install --build-from-source gmp
fi
