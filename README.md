JavaCPP Presets
===============

Introduction
------------
The JavaCPP Presets module contains Java configuration and interface classes for widely used C/C++ libraries. The configuration files in the `org.bytedeco.javacpp.presets` package are used by the `Parser` to create from C/C++ header files the Java interface files targeting the `org.bytedeco.javacpp` package, which is turn are used by the `Generator` and the native C++ compiler to produce the required JNI libraries. Moreover, helper classes make their functionality easier to use on the Java platform, including Android.

Please refer to the wiki page for more information about how to [create new presets](https://github.com/bytedeco/javacpp-presets/wiki/Create-New-Presets). Since additional documentation is currently lacking, please also feel free to ask questions on [the mailing list](http://groups.google.com/group/javacpp-project).


This Fork
=========

This is a fork of JavaCPP Presets which adds custom bindings to the LLVM C API
bridge. These bindings support debug information in PolyLLVM; the LLVM C
API lacks debug information support that exists in the C++ API.

Build Instructions
------------------

```
$ cd llvm
$ mvn install
```

Find the `.jar` files in the `llvm/target/` directory.

History
-------

Below is a list of steps for how this fork was created, in case further
hacking needs to be done in the future.

Clone the javacpp-presets repo (`git@github.com:bytedeco/javacpp-presets.git`)
and `cd` into the `llvm` directory.

Run `./cppbuild.sh install` to download and build the LLVM source.
It will take a while to build LLVM.

Find `DIBuilderBindings.{h,cpp}` and `IRBindings.{h,cpp}` in `cppbuild/<platform>/llvm-5.0.1.src/bindings/go/llvm/` where platform is (e.g.) macosx-x86_64. Copy to a local
`bindings` directory, and edit as necessary to support all API calls needed
for PolyLLVM.

Modify `cppbuild.sh` to automatically (1) copy the binding header files into `cppbuild/<platform>/llvm-5.0.1.src/include/llvm-c/`, (2) copy the binding header/implementation files into `cppbuild/<platform>/llvm-5.0.1.src/lib/IR/`, and (3) edit `cppbuild/macosx-x86_64/llvm-5.0.1.src/lib/IR/CMakeLists.txt` to include the two `.cpp` files from above.

Edit `src/main/java/org/bytedeco/javacpp/presets/LLVM.java` to

(1) include the two header files above:
    `include = { ..., "<llvm-c/DIBuilderBindings.h>", "<llvm-c/IRBindings.h>", ... }`

(2) map `LLVMOpaqueDIBuilder` to `LLVMDIBuilderRef`:
    `.put(new Info("LLVMOpaqueDIBuilder").pointerTypes("LLVMDIBuilderRef"))`

(3) specify value and pointer types for `LLVMDIBuilderRef`:
    `.put(new Info("LLVMDIBuilderRef").valueTypes("LLVMDIBuilderRef").pointerTypes("@ByPtrPtr LLVMDIBuilderRef", "@Cast(\"LLVMDIBuilderRef*\") PointerPointer"))`

Run `mvn install` to create the desired jar files under
`target/`, including `llvm.jar`, `llvm-sources.jar`, `llvm-<platform>.jar`, and
`llvm-javadoc.jar`.
