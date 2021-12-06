# RTLflow

A GPU acceleration flow for RTL simulation with multiple testbenches. RTLflow first transpiles RTL into CUDA kernels that each simulate a partition of the RTL simultaneously across multiple testbenches. It also leverages CUDA Graph for efficient runtime execution. We build RTLflow atop Verilator to inherit its existing optimization facilities, such as variable reduction and partitioning algorithms, that have been rigorously tested for over 25 years in the Verilator community.

# Comiple RTLflow
```bash
~$ cd verilator_rtlflow
~/verilator_rtlflow$ autoconf
~/verilator_rtlflow$ ./configure
~/verilator_rtlflow$ make -j8
```

# Use RTLflow
 To use RTLflow, you need:
 * Nvidia CUDA Toolkit and Compiler ([nvcc](https://developer.nvidia.com/cuda-llvm-compiler)) at least v10.0 with -std=c++14.
 * GNU C++ Compiler at least v5.0 with -std=c++14.
```bash
~$ nvcc --version    # NVCC must present with version at least v10.0
~$ g++ --version     # GNU must present with version at least v5.0
```

Open License
============


RTLflow is licensed with the MIT License.

Verilator is Copyright 2003-2021 by Wilson Snyder.

Verilator is free software; you can redistribute it and/or modify it under
the terms of either the GNU Lesser General Public License Version 3 or the
Perl Artistic License Version 2.0. See the documentation for more details.
