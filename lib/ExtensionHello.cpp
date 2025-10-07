#include "mlir/Analysis/SliceAnalysis.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/Transforms/Passes.h"
#include "triton/Dialect/Triton/IR/Utility.h"
#include "triton/Dialect/TritonGPU/IR/Dialect.h"
#include "triton/Dialect/TritonNvidiaGPU/IR/Dialect.h"

namespace mlir {
namespace triton {
namespace plugin {


#define GEN_PASS_DEF_TRITONGPUHELLOEXTENSION
#include "Passes.h.inc"


struct HelloExtensionPass :
  public impl::TritonGPUHelloExtensionBase<HelloExtensionPass> {
  void runOnOperation() override {
    llvm::errs() << "Hello From Triton Plugin Pass: HelloExtensionPass\n";

    MLIRContext *context = &getContext();
    ModuleOp mod = getOperation();
  }
};

} // namespace plugin
} // namespace triton
} // namespace mlir

extern "C" void addTritonPluginPass(mlir::PassManager* pm, mlir::ModuleOp *mod) {
  pm->addPass(mlir::triton::plugin::createTritonGPUHelloExtension());
}
