#ifndef LIB_TRANSFORM_PEREGRINEAFFINE_AFFINEFULLUNROLL_H_
#define LIB_TRANSFORM_PEREGRINEAFFINE_AFFINEFULLUNROLL_H_

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace tutorial {

#define GEN_PASS_DECL_AFFINEFULLUNROLL
#include "lib/Transform/PeregrineAffine/Passes.h.inc"

}  // namespace tutorial
}  // namespace mlir

#endif  // LIB_TRANSFORM_PEREGRINEAFFINE_AFFINEFULLUNROLL_H_
