//===- DIBuilderBindings.h - Bindings for DIBuilder -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines C bindings for the DIBuilder class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_BINDINGS_GO_LLVM_DIBUILDERBINDINGS_H
#define LLVM_BINDINGS_GO_LLVM_DIBUILDERBINDINGS_H

#include "IRBindings.h"
#include "llvm-c/Core.h"

#ifdef __cplusplus
extern "C" {
#endif

/// This enumeration defines the supported behaviors of module flags.
enum ModFlagBehavior {
  /// Emits an error if two values disagree, otherwise the resulting value is
  /// that of the operands.
  Error = 1,

  /// Emits a warning if two values disagree. The result value will be the
  /// operand for the flag from the first module being linked.
  Warning = 2,

  /// Adds a requirement that another module flag be present and have a
  /// specified value after linking is performed. The value must be a metadata
  /// pair, where the first element of the pair is the ID of the module flag
  /// to be restricted, and the second element of the pair is the value the
  /// module flag should be restricted to. This behavior can be used to
  /// restrict the allowable results (via triggering of an error) of linking
  /// IDs with the **Override** behavior.
  Require = 3,

  /// Uses the specified value, regardless of the behavior or value of the
  /// other module. If both modules specify **Override**, but the values
  /// differ, an error will be emitted.
  Override = 4,

  /// Appends the two values, which are required to be metadata nodes.
  Append = 5,

  /// Appends the two values, which are required to be metadata
  /// nodes. However, duplicate entries in the second list are dropped
  /// during the append operation.
  AppendUnique = 6,

  /// Takes the max of the two values, which are required to be integers.
  Max = 7,

  // Markers:
  ModFlagBehaviorFirstVal = Error,
  ModFlagBehaviorLastVal = Max
};

enum TypeKind {
  DW_ATE_address = 0x01,
  DW_ATE_boolean = 0x02,
  DW_ATE_complex_float = 0x03,
  DW_ATE_float = 0x04,
  DW_ATE_signed = 0x05,
  DW_ATE_signed_char = 0x06,
  DW_ATE_unsigned = 0x07,
  DW_ATE_unsigned_char = 0x08,
  DW_ATE_imaginary_float = 0x09,
  DW_ATE_packed_decimal = 0x0a,
  DW_ATE_numeric_string = 0x0b,
  DW_ATE_edited = 0x0c,
  DW_ATE_signed_fixed = 0x0d,
  DW_ATE_unsigned_fixed = 0x0e,
  DW_ATE_decimal_float = 0x0f,
  DW_ATE_UTF = 0x10,
  DW_ATE_UCS = 0x11,
  DW_ATE_ASCII = 0x12,
  DW_ATE_lo_user = 0x80,
  DW_ATE_hi_user = 0xff
};

enum SourceLanguage {
  DW_LANG_C89 = 0x0001,
  DW_LANG_C = 0x0002,
  DW_LANG_Ada83 = 0x0003,
  DW_LANG_C_plus_plus = 0x0004,
  DW_LANG_Cobol74 = 0x0005,
  DW_LANG_Cobol85 = 0x0006,
  DW_LANG_Fortran77 = 0x0007,
  DW_LANG_Fortran90 = 0x0008,
  DW_LANG_Pascal83 = 0x0009,
  DW_LANG_Modula2 = 0x000a,
  DW_LANG_Java = 0x000b,
  DW_LANG_C99 = 0x000c,
  DW_LANG_Ada95 = 0x000d,
  DW_LANG_Fortran95 = 0x000e,
  DW_LANG_PLI = 0x000f,
  DW_LANG_ObjC = 0x0010,
  DW_LANG_ObjC_plus_plus = 0x0011,
  DW_LANG_UPC = 0x0012,
  DW_LANG_D = 0x0013,
  DW_LANG_Python = 0x0014,
  DW_LANG_OpenCL = 0x0015,
  DW_LANG_Go = 0x0016,
  DW_LANG_Modula3 = 0x0017,
  DW_LANG_Haskell = 0x0018,
  DW_LANG_C_plus_plus_03 = 0x0019,
  DW_LANG_C_plus_plus_11 = 0x001a,
  DW_LANG_OCaml = 0x001b,
  DW_LANG_Rust = 0x001c,
  DW_LANG_C11 = 0x001d,
  DW_LANG_Swift = 0x001e,
  DW_LANG_Julia = 0x001f,
  DW_LANG_Dylan = 0x0020,
  DW_LANG_C_plus_plus_14 = 0x0021,
  DW_LANG_Fortran03 = 0x0022,
  DW_LANG_Fortran08 = 0x0023,
  DW_LANG_RenderScript = 0x0024,
  DW_LANG_BLISS = 0x0025,
  DW_LANG_Mips_Assembler = 0x8001,
  DW_LANG_GOOGLE_RenderScript = 0x8e57,
  DW_LANG_BORLAND_Delphi = 0xb000,
  DW_LANG_lo_user = 0x8000,
  DW_LANG_hi_user = 0xffff
};

void LLVMAddModuleFlag(LLVMModuleRef mod,
                       ModFlagBehavior behavior,
                       const char *key,
                       uint32_t val);

// The rest of the file is from the LLVM Go bindings.

typedef struct LLVMOpaqueDIBuilder *LLVMDIBuilderRef;

LLVMDIBuilderRef LLVMNewDIBuilder(LLVMModuleRef m);

void LLVMDIBuilderDestroy(LLVMDIBuilderRef d);
void LLVMDIBuilderFinalize(LLVMDIBuilderRef d);

LLVMMetadataRef
LLVMDIBuilderCreateCompileUnit(LLVMDIBuilderRef D, unsigned Language,
                               const char *File, const char *Dir,
                               const char *Producer, int Optimized,
                               const char *Flags, unsigned RuntimeVersion);

LLVMMetadataRef LLVMDIBuilderCreateFile(LLVMDIBuilderRef D, const char *File,
                                        const char *Dir);

LLVMMetadataRef LLVMDIBuilderCreateLexicalBlock(LLVMDIBuilderRef D,
                                                LLVMMetadataRef Scope,
                                                LLVMMetadataRef File,
                                                unsigned Line, unsigned Column);

LLVMMetadataRef LLVMDIBuilderCreateLexicalBlockFile(LLVMDIBuilderRef D,
                                                    LLVMMetadataRef Scope,
                                                    LLVMMetadataRef File,
                                                    unsigned Discriminator);

LLVMMetadataRef LLVMDIBuilderCreateFunction(
    LLVMDIBuilderRef D, LLVMMetadataRef Scope, const char *Name,
    const char *LinkageName, LLVMMetadataRef File, unsigned Line,
    LLVMMetadataRef CompositeType, int IsLocalToUnit, int IsDefinition,
    unsigned ScopeLine, unsigned Flags, int IsOptimized);

LLVMMetadataRef LLVMDIBuilderCreateAutoVariable(
    LLVMDIBuilderRef D, LLVMMetadataRef Scope, const char *Name,
    LLVMMetadataRef File, unsigned Line, LLVMMetadataRef Ty, int AlwaysPreserve,
    unsigned Flags, uint32_t AlignInBits);

LLVMMetadataRef LLVMDIBuilderCreateParameterVariable(
    LLVMDIBuilderRef D, LLVMMetadataRef Scope, const char *Name, unsigned ArgNo,
    LLVMMetadataRef File, unsigned Line, LLVMMetadataRef Ty, int AlwaysPreserve,
    unsigned Flags);

LLVMMetadataRef LLVMDIBuilderCreateBasicType(LLVMDIBuilderRef D,
                                             const char *Name,
                                             uint64_t SizeInBits,
                                             unsigned Encoding);

LLVMMetadataRef LLVMDIBuilderCreatePointerType(LLVMDIBuilderRef D,
                                               LLVMMetadataRef PointeeType,
                                               uint64_t SizeInBits,
                                               uint32_t AlignInBits,
                                               const char *Name);

LLVMMetadataRef
LLVMDIBuilderCreateSubroutineType(LLVMDIBuilderRef D, LLVMMetadataRef File,
                                  LLVMMetadataRef ParameterTypes);

LLVMMetadataRef LLVMDIBuilderCreateStructType(
    LLVMDIBuilderRef D, LLVMMetadataRef Scope, const char *Name,
    LLVMMetadataRef File, unsigned Line, uint64_t SizeInBits,
    uint32_t AlignInBits, unsigned Flags, LLVMMetadataRef DerivedFrom,
    LLVMMetadataRef ElementTypes);

LLVMMetadataRef LLVMDIBuilderCreateReplaceableCompositeType(
    LLVMDIBuilderRef D, unsigned Tag, const char *Name, LLVMMetadataRef Scope,
    LLVMMetadataRef File, unsigned Line, unsigned RuntimeLang,
    uint64_t SizeInBits, uint32_t AlignInBits, unsigned Flags);

LLVMMetadataRef
LLVMDIBuilderCreateMemberType(LLVMDIBuilderRef D, LLVMMetadataRef Scope,
                              const char *Name, LLVMMetadataRef File,
                              unsigned Line, uint64_t SizeInBits,
                              uint32_t AlignInBits, uint64_t OffsetInBits,
                              unsigned Flags, LLVMMetadataRef Ty);

LLVMMetadataRef LLVMDIBuilderCreateArrayType(LLVMDIBuilderRef D,
                                             uint64_t SizeInBits,
                                             uint32_t AlignInBits,
                                             LLVMMetadataRef ElementType,
                                             LLVMMetadataRef Subscripts);

LLVMMetadataRef LLVMDIBuilderCreateTypedef(LLVMDIBuilderRef D,
                                           LLVMMetadataRef Ty, const char *Name,
                                           LLVMMetadataRef File, unsigned Line,
                                           LLVMMetadataRef Context);

LLVMMetadataRef LLVMDIBuilderGetOrCreateSubrange(LLVMDIBuilderRef D, int64_t Lo,
                                                 int64_t Count);

LLVMMetadataRef LLVMDIBuilderGetOrCreateArray(LLVMDIBuilderRef D,
                                              LLVMMetadataRef *Data,
                                              size_t Length);

LLVMMetadataRef LLVMDIBuilderGetOrCreateTypeArray(LLVMDIBuilderRef D,
                                                  LLVMMetadataRef *Data,
                                                  size_t Length);

LLVMMetadataRef LLVMDIBuilderCreateExpression(LLVMDIBuilderRef Dref,
                                              int64_t *Addr, size_t Length);

LLVMValueRef LLVMDIBuilderInsertDeclareAtEnd(LLVMDIBuilderRef Dref,
                                             LLVMValueRef Storage,
                                             LLVMMetadataRef VarInfo,
                                             LLVMMetadataRef Expr,
                                             LLVMBasicBlockRef Block,
                                             unsigned Line,
                                             unsigned Col,
                                             LLVMMetadataRef Scope);

LLVMValueRef LLVMDIBuilderInsertValueAtEnd(LLVMDIBuilderRef Dref,
                                           LLVMValueRef Val, uint64_t Offset,
                                           LLVMMetadataRef VarInfo,
                                           LLVMMetadataRef Expr,
                                           LLVMBasicBlockRef Block,
                                           unsigned Line,
                                           unsigned Col,
                                           LLVMMetadataRef Scope);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
