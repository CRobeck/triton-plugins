#ifndef TRITONGPU_EXTENSION_PASSES_H
#define TRITONGPU_EXTENSION_PASSES_H

#include "mlir/Pass/Pass.h"

namespace mlir {

class ModuleOp;
template <typename T> class OperationPass;

namespace triton::gpu {

#define GEN_PASS_DECL
#include "Passes.h.inc"

std::unique_ptr<OperationPass<ModuleOp>> createTritonGPUHelloExtensionPass();

#define GEN_PASS_REGISTRATION
#include "Passes.h.inc"

} // namespace triton::gpu

} // namespace mlir

#endif // TRITONGPU_EXTENSION_PASSES_H
