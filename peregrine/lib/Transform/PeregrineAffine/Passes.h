#ifndef LIB_TRANSFORM_AFFINE_PASSES_H_
#define LIB_TRANSFORM_AFFINE_PASSES_H_

#include "lib/Transform/PeregrineAffine/AffineFullUnroll.h"
#include "lib/Transform/PeregrineAffine/AffineFullUnrollPatternRewrite.h"

namespace mlir {
namespace tutorial {

#define GEN_PASS_REGISTRATION
#include "lib/Transform/PeregrineAffine/Passes.h.inc"

}  // namespace tutorial
}  // namespace mlir

#endif  // LIB_TRANSFORM_AFFINE_PASSES_H_
