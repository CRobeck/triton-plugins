#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "triton/Analysis/Utility.h"
#include "mlir/Tools/Plugins/PassPlugin.h"
#include "Passes.h"

using namespace mlir;

namespace mlir::triton::gpu {
#define GEN_PASS_DEF_TRITONGPUHELLOEXTENSION
#include "Passes.h.inc"
}

// namespace {
// struct HelloExtension : public OpRewritePattern<DotOp> {
//   using OpRewritePattern::OpRewritePattern;
//   LogicalResult matchAndRewrite(DotOp dotOp,
//                                 PatternRewriter &rewriter) const override {
//     return success();
//   }
// };
// } // anonymous namespace
namespace {
struct TritonGPUHelloExtension :
  public mlir::triton::gpu::impl::TritonGPUHelloExtensionBase<TritonGPUHelloExtension> {
  void runOnOperation() override {
    llvm::errs() << "HelloExtensionPass\n";

    MLIRContext *context = &getContext();
    // ModuleOp mod = getOperation();
  //   mod.walk([&](FunctionOpInterface op) {
  //     llvm::errs() << op << "\n";
  //  });
    // OpPassManager pm;
    // if (failed(runPipeline(pm, m)))
    //   return signalPassFailure();
    // RewritePatternSet decomposePatterns(context);
    // decomposePatterns.add<HelloExtension>(context);
    // if (applyPatternsGreedily(m, std::move(decomposePatterns)).failed()) {
    //   signalPassFailure();
    // }
  }
};
} // namespace

namespace mlir::triton::gpu {
extern "C" LLVM_ATTRIBUTE_WEAK void addTritonPluginPass(mlir::PassManager* pm) {
  pm->addPass(createTritonGPUHelloExtensionPass());
}

// extern "C" LLVM_ATTRIBUTE_WEAK
// void registerTritonPluginPass() {
//   ::mlir::registerPass([]() -> std::unique_ptr<::mlir::Pass> {
//     return createTritonGPUHelloExtension();
//   });
// }

std::unique_ptr<OperationPass<ModuleOp>> createTritonGPUHelloExtensionPass() {
  return std::make_unique<TritonGPUHelloExtension>();
}
}
