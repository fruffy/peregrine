#ifndef LIB_DIALECT_PEREGRINE_PEREGRINETYPES_TD_
#define LIB_DIALECT_PEREGRINE_PEREGRINETYPES_TD_

include "PeregrineDialect.td"
include "mlir/IR/AttrTypeBase.td"

// A base class for all types in this dialect
class Peregrine_Type<string name, string typeMnemonic> : TypeDef<Peregrine_Dialect, name> {
  let mnemonic = typeMnemonic;
}

def Peregrine_Bool : Peregrine_Type<"Bool", "bool"> {
  let summary = "Boolean type";
}

def Peregrine_Bit : Peregrine_Type<"Bit", "bit"> {
  let summary = "Bit type";
  let parameters = (ins "int": $width);
  let assemblyFormat = "`<` $width `>`";
}

def Peregrine_Varbit : Peregrine_Type<"Varbit", "varbit"> {
  let summary = "Variable-length bit type";
  let parameters = (ins "int": $width);
  let assemblyFormat = "`<` $width `>`";
}

def Peregrine_Struct :
    Type<CPred<"$_self.isa<StructType>()">, "Peregrine struct type">;

#endif  // LIB_DIALECT_PEREGRINE_PEREGRINETYPES_TD_