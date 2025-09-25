// #include "mlir/Analysis/SliceAnalysis.h"
// #include "mlir/Dialect/SCF/IR/SCF.h"
// #include "mlir/IR/BuiltinAttributes.h"
// #include "mlir/IR/Dominance.h"
// #include "mlir/IR/IRMapping.h"
// #include "mlir/IR/Matchers.h"
// #include "mlir/IR/PatternMatch.h"
// #include "mlir/IR/Verifier.h"
// #include "mlir/Interfaces/InferTypeOpInterface.h"
// #include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
// #include "mlir/Support/LogicalResult.h"
// #include "mlir/Transforms/GreedyPatternRewriteDriver.h"
// #include "mlir/Transforms/Passes.h"
// #include "mlir/Transforms/RegionUtils.h"
#include "triton/Analysis/Utility.h"
// #include "triton/Dialect/Triton/IR/Dialect.h"
// #include "triton/Dialect/TritonGPU/IR/Dialect.h"
// #include "triton/Dialect/TritonGPU/Transforms/Passes.h"
// #include "triton/Dialect/TritonGPU/Transforms/TritonGPUConversion.h"
// #include "triton/Dialect/TritonGPU/Transforms/Utility.h"
// #include <deque>

// #include "mlir/IR/PatternMatch.h"
// #include "mlir/Transforms/GreedyPatternRewriteDriver.h"
// #include "triton/Dialect/TritonGPU/Transforms/Passes.h"

// #include "mlir/IR/MLIRContext.h"
// #include "mlir/InitAllDialects.h"
// #include "mlir/Tools/Plugins/DialectPlugin.h"

#include "mlir/Tools/Plugins/PassPlugin.h"
// #include "llvm/Config/llvm-config.h"
// #include "llvm/Support/Compiler.h"
// #include "mlir/Support/TypeID.h"

using namespace mlir;


// #include "mlir/Pass/Pass.h"
// #include "mlir/IR/PatternMatch.h"
// #include "mlir/Transforms/GreedyPatternRewriteDriver.h"
// #include "triton/Dialect/TritonGPU/Transforms/Passes.h"

// extern "C" void FOOBAR() { }

namespace mlir {
namespace triton {
namespace gpu {

#define GEN_PASS_DEF_TRITONGPUHELLOEXTENSION
#include "Passes.h.inc"

// namespace {
// struct HelloExtension : public OpRewritePattern<DotOp> {
//   using OpRewritePattern::OpRewritePattern;
//   LogicalResult matchAndRewrite(DotOp dotOp,
//                                 PatternRewriter &rewriter) const override {
//     return success();
//   }
// };
// } // anonymous namespace

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
  llvm::errs() << "addTritonPluginPass\n";
  pm->addPass(createTritonGPUHelloExtension());
}

extern "C" LLVM_ATTRIBUTE_WEAK
void registerTritonGPUHelloExtension() {
  llvm::errs() << "registerTritonGPUHelloExtension\n";
  ::mlir::registerPass([]() -> std::unique_ptr<::mlir::Pass> {
    return createTritonGPUHelloExtension();
  });
}
} // namespace gpu
} // namespace triton
} // namespace mlir


// void registerPasses() {
//   llvm::errs() << "registerPasses\n";
//   ::mlir::registerPass([]() -> std::unique_ptr<::mlir::Pass> {
//     return mlir::triton::gpu::createTritonGPUHelloExtension();
//   });
// }


// /// Pass plugin registration mechanism.
// /// Necessary symbol to register the pass plugin.
// extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo mlirGetPassPluginInfo() {
//   llvm::errs() << "mlirGetPassPluginInfo\n";
//   return {MLIR_PLUGIN_API_VERSION, "HelloExtensionPlugin", LLVM_VERSION_STRING,
//           []() {registerPasses();
//           }};
// }
