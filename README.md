# RTLflow <img align="right" src="./logo.png" />

A GPU acceleration flow for RTL simulation with batch stimulus. 


# What is RTLflow?
RTLflow is a GPU acceleration flow for RTL simulation with batch stimulus. RTLflow first transpiles RTL into CUDA kernels that each simulate a partition of the RTL simultaneously across multiple stimulus. It also leverages CUDA Graph for efficient runtime execution. We build RTLflow atop Verilator to inherit its existing optimization facilities, such as variable reduction and partitioning algorithms, that have been rigorously tested for over 25 years in the Verilator community.

# For the newest verison of RTLflow, please switch to pipeline branch

# Compile RTLflow
```bash
~$ cd RTLflow
~/RTLflow$ autoconf
~/RTLflow$ ./configure
~/RTLflow$ make -j8
```

# Use RTLflow
 To use RTLflow, you need:
 * Nvidia CUDA Toolkit and Compiler ([nvcc](https://developer.nvidia.com/cuda-llvm-compiler)) at least v11.0 with -std=c++17.
 * GNU C++ Compiler at least v5.0 with -std=c++17.
```bash
~$ nvcc --version    # NVCC must present with version at least v11.0
~$ g++ --version     # GNU must present with version at least v8.0
```

You will also need to set ```$VERILATOR_ROOT``` to RTLflow root directory before using RTLflow. For example:
```bash
~$ export VERILATOR_ROOT=~/RTLflow
```

By default, we set nvcc flag ```--arch=sm_80``` to achieve the best performance under our enviornment. You can go to:
```bash
~/RTLflow/include/verilated.mk.in
```
to modify ```$RTLFLOW_FLAGS``` and ```make``` RTLflow again.


Open License
============


RTLflow is licensed with the MIT License.


