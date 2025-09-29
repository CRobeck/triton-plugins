#include "mlir/Analysis/SliceAnalysis.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/Transforms/Passes.h"
#include "triton/Dialect/Triton/IR/Utility.h"
#include "triton/Dialect/TritonGPU/IR/Dialect.h"
#include "triton/Dialect/TritonInstrument/IR/Dialect.h"
#include "triton/Dialect/TritonInstrument/IR/Utility.h"
#include "triton/Dialect/TritonNvidiaGPU/IR/Dialect.h"
// #include "RegisterTritonDialects.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Dialect/LLVMIR/Transforms/InlinerInterfaceImpl.h"

#include "mlir/Target/LLVMIR/Dialect/Builtin/BuiltinToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Dialect/LLVMIR/LLVMToLLVMIRTranslation.h"
namespace mlir {
namespace triton {
namespace instrument {


#define GEN_PASS_DEF_TRITONINSTRUMENTCONCURRENCYSANITIZER
#include "triton/Dialect/TritonInstrument/Transforms/Passes.h.inc"
namespace {

// class StandaloneSwitchBarFooRewriter : public OpRewritePattern<func::FuncOp> {
// public:
//   using OpRewritePattern<func::FuncOp>::OpRewritePattern;
//   LogicalResult matchAndRewrite(func::FuncOp op,
//                                 PatternRewriter &rewriter) const final {
//     llvm::errs() << "op" << "\n";
//       return success();
//   }
// };

class ConcurrencySanitizerPass
    : public impl::TritonInstrumentConcurrencySanitizerBase<
          ConcurrencySanitizerPass> {
public:
  // void getDependentDialects(DialectRegistry &registry) const override {
    // registry.insert<mlir::triton::gpu::TritonGPUDialect>();
    // registry.insert<mlir::triton::TritonDialect>();
    // registry.insert<mlir::triton::instrument::TritonInstrumentDialect>();
  // }
  void runOnOperation() override {
    auto context = &getContext();
    // context->loadDialect<mlir::triton::instrument::TritonInstrumentDialect>();
    // DialectRegistry registry;
    llvm::errs() << "HelloExtensionPass\n";
    // auto module = getOperation();
  //   RewritePatternSet patterns(&getContext());
  //   patterns.add<StandaloneSwitchBarFooRewriter>(&getContext());
  //   FrozenRewritePatternSet patternSet(std::move(patterns));
  //   if (failed(applyPatternsGreedily(getOperation(), patternSet)))
  //     signalPassFailure();
  }
};
}

} // namespace instrument
} // namespace triton
} // namespace mlir

namespace mlir::triton::instrument {
extern "C" LLVM_ATTRIBUTE_WEAK void addTritonPluginPass(mlir::PassManager* pm) {
  // pm->getPasses();

  // registerTritonDialects(registry);
  pm->addPass(createTritonInstrumentConcurrencySanitizer());
  // DialectRegistry registry;
  // registry.insert<::mlir::triton::instrument::TritonInstrumentDialect>();
  // mlir::standalone::registerPasses();
}
}

extern "C" LLVM_ATTRIBUTE_WEAK
void registerPluginDialect( mlir::DialectRegistry &registry) {

  // registry.insert<mlir::triton::instrument::TritonInstrumentDialect>();
  // context.appendDialectRegistry(registry);
}
