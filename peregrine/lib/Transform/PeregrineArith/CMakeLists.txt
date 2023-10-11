add_mlir_library(MulToAdd
    MulToAdd.cpp

    ${PEREGRINE_SOURCE_DIR}/lib/Transform/PeregrineArith/
    ADDITIONAL_HEADER_DIRS
    LINK_LIBS PUBLIC
)

set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name PeregrineArith)
add_public_tablegen_target(MLIRMulToAddPasses)
add_mlir_doc(Passes PeregrineArithPasses ./ -gen-pass-doc)
