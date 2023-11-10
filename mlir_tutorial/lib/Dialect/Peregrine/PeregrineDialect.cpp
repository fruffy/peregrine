#include "lib/Dialect/Peregrine/PeregrineDialect.h"
#include "lib/Dialect/Peregrine/PeregrineTypes.h"
#include "mlir/include/mlir/IR/Builders.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"

#include "lib/Dialect/Peregrine/PeregrineDialect.cpp.inc"
#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Peregrine/PeregrineTypes.cpp.inc"

namespace peregrine
{

    void PeregrineDialect::initialize()
    {
        addTypes<
#define GET_TYPEDEF_LIST
#include "lib/Dialect/Peregrine/PeregrineTypes.cpp.inc"
            >();

        addTypes<StructType>();
    }

    struct StructTypeStorage : public mlir::TypeStorage
    {
        using KeyTy = llvm::ArrayRef<mlir::Type>;

        StructTypeStorage(llvm::ArrayRef<mlir::Type> elementTypes)
            : elementTypes(elementTypes) {}

        bool operator==(const KeyTy &key) const { return key == elementTypes; }

        static llvm::hash_code hashKey(const KeyTy &key)
        {
            return llvm::hash_value(key);
        }

        static KeyTy getKey(llvm::ArrayRef<mlir::Type> elementTypes)
        {
            return KeyTy(elementTypes);
        }

        static StructTypeStorage *construct(mlir::TypeStorageAllocator &allocator,
                                            const KeyTy &key)
        {
            // Copy the elements from the provided `KeyTy` into the allocator.
            llvm::ArrayRef<mlir::Type> elementTypes = allocator.copyInto(key);

            // Allocate the storage instance and construct it.
            return new (allocator.allocate<StructTypeStorage>())
                StructTypeStorage(elementTypes);
        }

        /// The following field contains the element types of the struct.
        llvm::ArrayRef<mlir::Type> elementTypes;
    };

    class StructType : public mlir::Type::TypeBase<StructType, mlir::Type,
                                                   StructTypeStorage>
    {
    public:
        using Base::Base;

        static StructType get(llvm::ArrayRef<mlir::Type> elementTypes)
        {
            assert(!elementTypes.empty() && "expected at least 1 element type");

            mlir::MLIRContext *ctx = elementTypes.front().getContext();
            return Base::get(ctx, elementTypes);
        }

        /// Returns the element types of this struct type.
        llvm::ArrayRef<mlir::Type> getElementTypes()
        {
            // 'getImpl' returns a pointer to the internal storage instance.
            return getImpl()->elementTypes;
        }

        /// Returns the number of element type held by this struct.
        size_t getNumElementTypes() { return getElementTypes().size(); }
    };

} // namespace peregrine
