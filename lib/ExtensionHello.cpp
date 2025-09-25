 #include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "triton/Analysis/Utility.h"
#include "mlir/Tools/Plugins/PassPlugin.h"


using namespace mlir;

namespace mlir {
namespace triton {
namespace gpu {

#define GEN_PASS_DEF_TRITONGPUHELLOEXTENSION
#include "Passes.h.inc"

namespace {
struct HelloExtension : public OpRewritePattern<DotOp> {
  using OpRewritePattern::OpRewritePattern;
  LogicalResult matchAndRewrite(DotOp dotOp,
                                PatternRewriter &rewriter) const override {
    return success();
  }
};
} // anonymous namespace

struct HelloExtensionPass :
  public impl::TritonGPUHelloExtensionBase<HelloExtensionPass> {
  void runOnOperation() override {
    llvm::errs() << "HelloExtensionPass\n";

    // MLIRContext *context = &getContext();
    // ModuleOp m = getOperation();
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



extern "C" LLVM_ATTRIBUTE_WEAK void addTritonPluginPass(mlir::PassManager* pm) {
  pm->addPass(createTritonGPUHelloExtension());
}

extern "C" LLVM_ATTRIBUTE_WEAK
void registerTritonPluginPass() {
  ::mlir::registerPass([]() -> std::unique_ptr<::mlir::Pass> {
    return createTritonGPUHelloExtension();
  });
}
} // namespace gpu
} // namespace triton
} // namespace mlir
