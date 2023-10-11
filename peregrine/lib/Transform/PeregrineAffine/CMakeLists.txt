add_mlir_library(AffineFullUnroll
    AffineFullUnroll.cpp
    AffineFullUnrollPatternRewrite.cpp

    ${PEREGRINE_SOURCE_DIR}/lib/Transform/PeregrineAffine/
    ADDITIONAL_HEADER_DIRS
    LINK_LIBS PUBLIC
)

set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name PeregrineAffine)
add_public_tablegen_target(MLIRAffineFullUnrollPasses)
add_mlir_doc(Passes PeregrineAffinePasses ./ -gen-pass-doc)

