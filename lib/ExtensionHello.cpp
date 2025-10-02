#include "mlir/Analysis/SliceAnalysis.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/Transforms/Passes.h"
#include "triton/Dialect/Triton/IR/Utility.h"
#include "triton/Dialect/TritonGPU/IR/Dialect.h"
#include "triton/Dialect/TritonInstrument/IR/Dialect.h"
#include "triton/Dialect/TritonInstrument/IR/Utility.h"
#include "triton/Dialect/TritonNvidiaGPU/IR/Dialect.h"

// namespace mlir {
// namespace triton {
// namespace instrument {

// namespace tt = mlir::triton;
// namespace ttg = mlir::triton::gpu;
// namespace ttng = mlir::triton::nvidia_gpu;
// namespace tti = mlir::triton::instrument;

// #define GEN_PASS_DEF_TRITONINSTRUMENTCONCURRENCYSANITIZER
// #include "triton/Dialect/TritonInstrument/Transforms/Passes.h.inc"

// class ConcurrencySanitizerPass
//     : public impl::TritonInstrumentConcurrencySanitizerBase<
//           ConcurrencySanitizerPass> {
// public:
//   void runOnOperation() override {
//     // auto module = getOperation();
//     // llvm::errs() << "ConcurrencySanitizerPassPlugin\n";
//   }
// };

// } // namespace instrument
// } // namespace triton
// } // namespace mlir

void addTritonPluginPass(mlir::PassManager& pm, mlir::ModuleOp &mod) {
    llvm::errs() << "Inside dynamic library\n";
    llvm::errs() << mod->getName() << "\n";
    llvm::errs() << mod->isRegistered() << "\n";
    llvm::errs() << sizeof(mod) << "\n";
    llvm::errs() << typeid(mod).name() << "\n";
    // llvm::errs() << mod << "\n";
}
