cmake_minimum_required(VERSION 3.21)
project(triton-plugins LANGUAGES C CXX)

# Set compilers
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

# Confirm that the LLVM installation directory exists
set(LLVM_INCLUDE_DIR "${LLVM_INSTALL_DIR}/include/llvm")
if(NOT EXISTS "${LLVM_INCLUDE_DIR}")
message(FATAL_ERROR
  " LLVM_INSTALL_DIR (${LLVM_INCLUDE_DIR}) is invalid.")
endif()

# Check that the LLVMConfig.cmake file exists
set(- FALSE)

# Ubuntu + Darwin
if(EXISTS "${LLVM_INSTALL_DIR}/lib/cmake/llvm/LLVMConfig.cmake")
  set(VALID_INSTALLATION TRUE)
endif()
# Fedora
if(EXISTS "${LLVM_INSTALL_DIR}/lib64/cmake/llvm/LLVMConfig.cmake")
  set(VALID_INSTALLATION TRUE)
endif()
if(NOT ${VALID_INSTALLATION})
  message(FATAL_ERROR
    "LLVM installation directory, (${LLVM_INSTALL_DIR}), is invalid. Couldn't
    find LLVMConfig.cmake.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${LLVM_INSTALL_DIR}/lib/cmake/llvm/")
find_package(LLVM)

if("${LLVM_VERSION_MAJOR}" VERSION_LESS 17)
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 17 or above")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} in ${LLVM_INSTALL_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_INSTALL_DIR}")
message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}
  Targets     ${LLVM_TARGETS_TO_BUILD}"
)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(MLIR_DIR ${LLVM_LIBRARY_DIRS}/cmake/mlir)
set(LLD_DIR ${LLVM_LIBRARY_DIRS}/cmake/lld)


# MLIR
find_package(MLIR REQUIRED CONFIG PATHS ${MLIR_DIR})

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${TRITON_BASE_DIR}/cmake")

include(TableGen) # required by AddMLIR
include(AddLLVM)
include(AddMLIR)

function(add_triton_object name)
  cmake_parse_arguments(ARG "" "" "DEPENDS;LINK_LIBS" ${ARGN})
  add_library(${name} OBJECT)
  target_sources(${name}
    PRIVATE ${ARG_UNPARSED_ARGUMENTS}
    INTERFACE $<TARGET_OBJECTS:${name}>
  )


  # add_library(${name} OBJECT ${ARG_UNPARSED_ARGUMENTS})
  if(ARG_DEPENDS)
    add_dependencies(${name} ${ARG_DEPENDS})
  endif()
  if(ARG_LINK_LIBS)
    target_link_libraries(${name} PUBLIC ${ARG_LINK_LIBS})
  endif()
endfunction(add_triton_object)

set_property(GLOBAL PROPERTY TRITON_LIBS "")
function(add_triton_library name)
  set_property(GLOBAL APPEND PROPERTY TRITON_LIBS ${name})
  add_triton_object(${name} ${ARGN})
  llvm_update_compile_flags(${name})
  message(STATUS "TRITON_LIB: ${name}")
endfunction()

include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(SYSTEM "${TRITON_BASE_DIR}")
include_directories(SYSTEM "${TRITON_BASE_DIR}/include")
include_directories(SYSTEM "${TRITON_BASE_DIR}/third_party")
include_directories(SYSTEM "${TRITON_INSTALL_DIR}/include")
include_directories(SYSTEM "${TRITON_INSTALL_DIR}/third_party")
include_directories(SYSTEM "${PROJECT_BINARY_DIR}/lib") # Tablegen'd files
include_directories(SYSTEM "/home/robeck/triton-plugins/build/TRITON_LIBS/Dialect/Triton/IR/")
include_directories(SYSTEM "/home/robeck/triton-plugins/build/TRITON_LIBS/Dialect/Triton/Transforms/")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE
      STRING "Build type (default Debug):" FORCE)
endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
#   -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function \
#   -DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING \
#   -fdiagnostics-color=always")

#if(NOT LLVM_ENABLE_RTTI)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")
#endif()

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fvisibility-inlines-hidden" SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG)
if (${SUPPORTS_FVISIBILITY_INLINES_HIDDEN_FLAG} EQUAL "1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the build directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(lib)
add_subdirectory(${TRITON_BASE_DIR}/include TRITON_INCLUDES)
add_subdirectory(${TRITON_BASE_DIR}/lib TRITON_LIBS)
add_subdirectory(${TRITON_BASE_DIR}/third_party/f2reduce F2REDUCE2_LIBS)
