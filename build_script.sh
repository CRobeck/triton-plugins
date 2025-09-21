mkdir build && cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_INSTALL_DIR=/Users/corbin/.triton/llvm/llvm-064f02da-macos-arm64/ ..
cmake --build .
