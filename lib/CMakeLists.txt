set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name Extensions)
# add_public_tablegen_target(TritonTableGen)
add_public_tablegen_target(TritonGPUExtensionIncGen)
# add_public_tablegen_target(TritonGPUTableGen)
# add_public_tablegen_target(TritonGPUAttrDefsIncGen)
# add_public_tablegen_target(TritonGPUTypeInterfacesIncGen)
# add_public_tablegen_target(TritonGPUOpInterfacesIncGen)

set(GPU_EXTENSION_PASSES
    GPUExtensionTestLib
    )

set(GPUExtensionTestLib_SOURCES
    ExtensionHello.cpp
    )


# MODULE

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
        # TritonGPUTableGen
        # TritonGPUAttrDefsIncGen
        # TritonGPUTypeInterfacesIncGen
        # TritonGPUOpInterfacesIncGen

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
        "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>"
        ${TRITON_LIB_DIR}/libtriton.so
        )
    set_target_properties(${plugin} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                          ${PROJECT_BINARY_DIR}/lib)



    # This is set to -fvisibility=hidden in the top level CMake file
    # which causes the llvmGetPassPluginInfo symbol to be hidden and
    # an "entry point not found" error. Reset it just for this target
    if(NOT MSVC)
      target_compile_options(${plugin} PRIVATE -fvisibility=default)
    endif()
endforeach()
