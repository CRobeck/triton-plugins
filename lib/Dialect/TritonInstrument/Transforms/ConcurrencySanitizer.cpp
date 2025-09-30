#include "mlir/Transforms/Passes.h"
#include "triton/Dialect/TritonInstrument/IR/Dialect.h"

namespace mlir {
namespace triton {
namespace instrument {


#define GEN_PASS_DEF_TRITONINSTRUMENTCONCURRENCYSANITIZER
#include "triton/Dialect/TritonInstrument/Transforms/Passes.h.inc"


class ConcurrencySanitizerPass
    : public impl::TritonInstrumentConcurrencySanitizerBase<
          ConcurrencySanitizerPass> {
public:
  void runOnOperation() override {
    llvm::errs() << "HelloExtensionPassPlugin\n";
    module = getOperation();
  }

private:

  ModuleOp module;
};

} // namespace instrument
} // namespace triton
} // namespace mlir

extern "C" LLVM_ATTRIBUTE_WEAK void addTritonPluginPass(mlir::PassManager& pm, std::unique_ptr< ::mlir::Pass> &PluginPass) {
  llvm::errs() << "HelloExtensionPassPlugin\n";
  PluginPass = std::make_unique<mlir::triton::instrument::ConcurrencySanitizerPass>();
  // std::make_unique<mlir::triton::instrument::ConcurrencySanitizerPass>();
  // pm->addPass(mlir::triton::instrument::createTritonInstrumentConcurrencySanitizer());
}

// std::unique_ptr<::mlir::Pass> createTritonInstrumentConcurrencySanitizer() {
//     return std::make_unique<ConcurrencySanitizerPass>();
//   }
