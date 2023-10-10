
sudo apt install clang lld cmake

mkdir -p build
cd build
cmake -G Ninja `third_party/llvm//llvm` \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DLLVM_TARGETS_TO_BUILD=host \
    -DLLVM_ENABLE_PROJECTS=mlir \
    -DLLVM_INSTALL_UTILS=ON \
    -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
    -DLLVM_EXTERNAL_PROJECTS=mlir-peregrine \
    -DLLVM_EXTERNAL_STANDALONE_DIALECT_SOURCE_DIR=../ \
    -DLLVM_ENABLE_LLD=ON  -DLLVM_CCACHE_BUILD=ON \
    -DLLVM_ENABLE_ASSERTIONS=ON
cmake --build . --target check-peregrine

