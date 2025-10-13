set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name Extensions)
add_public_tablegen_target(TritonGPUExtensionIncGen)

llvm_canonicalize_cmake_booleans(
  MLIR_ENABLE_BINDINGS_PYTHON
)

set(GPU_EXTENSION_PASSES
    GPUExtensionTestLib
    )

set(GPUExtensionTestLib_SOURCES
    ExtensionHello.cpp
    )

get_property(triton_libs GLOBAL PROPERTY TRITON_LIBS)
get_property(f2reduce_libs GLOBAL PROPERTY F2REDUCE2_LIBS)

foreach( plugin ${GPU_EXTENSION_PASSES} )
    add_mlir_library(${plugin}
        ${${plugin}_SOURCES}
        SHARED

        ADDITIONAL_HEADER_DIRS
        ${PROJECT_BINARY_DIR}/lib

        DEPENDS
        TritonTableGen
        TritonCanonicalizeIncGen
        TritonGPUExtensionIncGen

        LINK_LIBS PUBLIC
        ${triton_libs}
        ${f2reduce_libs}
        MLIRIR
        MLIRInferTypeOpInterface
        MLIRFunctionInterfaces
        MLIRFuncDialect
        MLIRPass
        LLVMSupport
        MLIRSupport
        TritonGPUIR
        TritonNvidiaGPUIR
        TritonInstrumentIR
        MLIROptLib
        MLIRPass
        MLIRRegisterAllDialects
        MLIRRegisterAllPasses
        MLIRTransforms
        Python3::Module
        pybind11::headers
        "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>"
        # ${TRITON_LIB_DIR}/libtriton.so
        )
    set_target_properties(${plugin} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                          ${PROJECT_BINARY_DIR}/lib)
    target_link_options(${plugin} PRIVATE -rdynamic)

      target_compile_options(${plugin} PRIVATE -fvisibility=default -fPIC)
      target_compile_definitions(${plugin} PUBLIC _GLIBCXX_USE_CXX11_ABI=1)
    target_link_libraries(${plugin} ${Python_LIBRARIES})
    target_link_options(${plugin} PRIVATE ${PYTHON_LDFLAGS} -Wl,--no-as-needed)
endforeach()
