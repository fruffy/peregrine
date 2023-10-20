load("@llvm-project//mlir:tblgen.bzl", "gentbl_cc_library", "td_library")

package(
    default_visibility = ["//visibility:public"],
)

td_library(
    name = "td_files",
    srcs = [
        "PeregrineDialect.td",
        "PeregrineTypes.td",
    ],
    includes = ["@heir//include"],
    deps = [
        # the base mlir target for defining operations and dialects in tablegen
        "@llvm-project//mlir:OpBaseTdFiles",
    ],
)

gentbl_cc_library(
    name = "dialect_inc_gen",
    tbl_outs = [
        (
            ["-gen-dialect-decls"],
            "PeregrineDialect.h.inc",
        ),
        (
            ["-gen-dialect-defs"],
            "PeregrineDialect.cpp.inc",
        ),
    ],
    tblgen = "@llvm-project//mlir:mlir-tblgen",
    td_file = "PeregrineDialect.td",
    deps = [
        ":td_files",
    ],
)

gentbl_cc_library(
    name = "types_inc_gen",
    tbl_outs = [
        (
            ["-gen-typedef-decls"],
            "PeregrineTypes.h.inc",
        ),
        (
            ["-gen-typedef-defs"],
            "PeregrineTypes.cpp.inc",
        ),
    ],
    tblgen = "@llvm-project//mlir:mlir-tblgen",
    td_file = "PeregrineTypes.td",
    deps = [
        ":dialect_inc_gen",
        ":td_files",
    ],
)

cc_library(
    name = "Peregrine",
    srcs = ["PeregrineDialect.cpp"],
    hdrs = ["PeregrineDialect.h", "PeregrineTypes.h"],
    deps = [
        ":dialect_inc_gen",
        ":types_inc_gen",
        "@llvm-project//mlir:IR",
        "@llvm-project//mlir:Support",
    ],
)