include "mlir/IR/DialectBase.td"

def Peregrine_Dialect : Dialect {
    let name = "peregrine";
    let summary = "A high-level dialect for analyzing and optimizing packet processing languages.";
    let description = [{
        This dialect provides a representation of the language that is amenable to analysis and optimization.
    }];
    let cppNamespace = "peregrine";
    let useDefaultTypePrinterParser = 1;
}