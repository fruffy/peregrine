#!/bin/bash
set -e  # Exit on error.
set -x  # Make command execution verbose

THIS_DIR=$( cd -- "$( dirname -- "${0}" )" &> /dev/null && pwd )

sudo apt install clang lld cmake

mkdir -p build
cd build
cmake -G Ninja ${THIS_DIR}/third_party/llvm/llvm \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DLLVM_TARGETS_TO_BUILD="Native;NVPTX;AMDGPU" \
    -DLLVM_ENABLE_PROJECTS=mlir \
    -DLLVM_INSTALL_UTILS=ON \
    -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
    -DLLVM_EXTERNAL_PROJECTS=mlir-peregrine \
    -DLLVM_EXTERNAL_MLIR_PEREGRINE_SOURCE_DIR=${THIS_DIR} \
    -DLLVM_ENABLE_LLD=ON  -DLLVM_CCACHE_BUILD=ON \
    -DLLVM_ENABLE_ASSERTIONS=ON
cmake --build . --target check-peregrine

