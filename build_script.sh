#export LLVM_BUILD_DIR=\`pwd\`/llvm-project/build
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/.conda/envs/triton/lib

cmake -DCMAKE_C_COMPILER=clang \
-DCMAKE_CXX_COMPILER=clang++ \
-DLLVM_INSTALL_DIR=/home/robeck/.triton/llvm/llvm-064f02da-ubuntu-x64 \
-DTRITON_BASE_DIR=/home/robeck/triton \
-DTRITON_INSTALL_DIR=/home/robeck/triton/build/cmake.linux-x86_64-cpython-3.11 \
-DTRITON_LIB_DIR=/home/robeck/triton/python/triton/_C/ \
..
