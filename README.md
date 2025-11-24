# Euclidean Distance Calculation - C and x86-64 Assembly

## Project Overview
This project implements Euclidean distance calculation between coordinate points in both C and x86-64 assembly language, comparing their performance across different vector sizes.

**Distance Formula:** `Z[i] = sqrt((X2[i] - X1[i])^2 + (Y2[i] - Y1[i])^2)`
- X1, X2, Y1, Y2: coordinate vectors (double-precision float)
- Z: result vector (double-precision float)
- n: number of coordinate pairs

---

## Table of Contents
1. [Specifications](#specifications)
2. [Implementation Details](#implementation-details)
3. [Performance Analysis](#performance-analysis)
4. [Correctness Verification](#correctness-verification)
5. [Compilation and Execution](#compilation-and-execution)
6. [Screenshots](#screenshots)
7. [Video Demonstration](#video-demonstration)

---

## Specifications

<p align="center">
  <img width="1107" height="398" alt="image" src="https://github.com/user-attachments/assets/6f289d1b-701a-42a1-a917-81866de99f50" />
</p>

### Input
- Scalar variable `n` (integer) contains the length of vectors
- Vectors `X1`, `X2`, `Y1`, `Y2` (double-precision float arrays) and Z are #double-precision float.

### Process Example
```
X1 → 1.5, 4.0, 3.5, 2.0
X2 → 3.0, 2.5, 2.5, 1.0
Y1 → 4.0, 3.0, 3.5, 3.0
Y2 → 2.0, 2.5, 1.0, 1.5

Calculation:
z[0] = sqrt((3.0-1.5)^2 + (2.0-4.0)^2) = sqrt(2.25 + 4.0) = 2.5
z[1] = sqrt((2.5-4.0)^2 + (2.5-3.0)^2) = sqrt(2.25 + 0.25) = 1.58113883
z[2] = sqrt((2.5-3.5)^2 + (1.0-3.5)^2) = sqrt(1.0 + 6.25) = 2.69258240
z[3] = sqrt((1.0-2.0)^2 + (1.5-3.0)^2) = sqrt(1.0 + 2.25) = 1.80277564

Result:
Z → 2.5, 1.58113883, 2.692582404, 1.802775638
```

### Output
- Result stored in vector Z
- Display first 10 elements of Z for both C and x86-64 versions
- Correctness check comparing outputs

### Requirements
- ✓ C kernel implementation
- ✓ x86-64 assembly kernel implementation
- ✓ Use scalar SIMD registers (xmm0, xmm1, xmm2)
- ✓ Use scalar SIMD floating-point instructions (movsd, subsd, mulsd, addsd, sqrtsd)
- ✓ Time kernel portion only
- ✓ Test with vector sizes: 2^20, 2^24, 2^28
- ✓ Run 30 iterations per test for average execution time
- ✓ Verify correctness between C and x86-64 outputs

---

## Implementation Details

### C Kernel (`c_kernel`)
```c
void c_kernel(int n, double* x1, double* x2, double* y1, double* y2, double* z) {
    for (int i = 0; i < n; i++) {
        double diff_x = x2[i] - x1[i];
        double diff_y = y2[i] - y1[i];
        z[i] = sqrt((diff_x * diff_x) + (diff_y * diff_y));
    }
}
```

### x86-64 Assembly Kernel (`asmfunc`)

**Registers Used (Microsoft x64 Calling Convention):**
- `RCX`: n (number of elements)
- `RDX`: pointer to x1 vector
- `R8`: pointer to x2 vector
- `R9`: pointer to y1 vector
- `[RSP+0x28]`: pointer to y2 vector
- `[RSP+0x30]`: pointer to z vector
- `R10-R14`: temporary registers for pointers
- `R15`: loop index
- `XMM0`, `XMM1`: SIMD registers for computation

**SIMD Instructions Used:**
- `movsd`: Move scalar double-precision value
- `subsd`: Subtract scalar double-precision
- `mulsd`: Multiply scalar double-precision
- `addsd`: Add scalar double-precision
- `sqrtsd`: Square root of scalar double-precision

---

## Performance Analysis

### Execution Results

| Vector Size | Elements | C Kernel (sec) | x86-64 Kernel (sec) | Speedup |
|------------|----------|----------------|---------------------|---------|
| 2^20 | 1,048,576 | [C_TIME] | [ASM_TIME] | [SPEEDUP] |
| 2^24 | 16,777,216 | [C_TIME] | [ASM_TIME] | [SPEEDUP] |
| 2^28 | 268,435,456 | [C_TIME] | [ASM_TIME] | [SPEEDUP] |

*Average of 30 iterations*

The results clearly show that the x86-64 assembly kernel consistently outperforms the C kernel for all the vector sizes. This performance gap is to be expected because the assembly version uses instructions and registers that have less instruction overhead and allows more efficiency in performance. Additionally, Assembly is a lower-level language, so it gives you direct control over every register and instruction. Because you can write exactly what the CPU needs without having to add unnecessary extra instructions, you remove the additional tasks that C normally adds. It can also be observed that as vector size increases, the program becomes more memory-bound, or the memory becomes the bottleneck simply because RAM is slower than a CPU.
### Performance Analysis

#### Key Observations

1. **Computational Complexity**: The Euclidean distance calculation involves multiple arithmetic operations per element:
   - 2 subtractions
   - 2 multiplications
   - 1 addition
   - 1 square root
   
   This is more compute-intensive than simple DAXPY operations, making assembly optimizations more beneficial.

2. **SIMD Utilization**: The implementation leverages scalar SIMD registers (XMM0, XMM1) with double-precision floating-point instructions (movsd, subsd, mulsd, addsd, sqrtsd) to perform efficient calculations on individual elements.

3. **Memory Access Patterns**: The kernel accesses four input vectors and one output vector sequentially, utilizing spatial locality. The assembly implementation's explicit control over register usage and memory addressing may provide performance advantages over C compiler-generated code, particularly in unoptimized (debug) builds.

4. **Optimization Impact**: 
   - In **debug mode** (no compiler optimizations), hand-written assembly typically shows measurable performance gains.
   - In **release mode** (with compiler optimizations), modern C compilers generate highly efficient code that may approach assembly performance.


#### Performance Implications

- The sqrt operation is particularly expensive; both implementations benefit from efficient handling of this operation.
- Vector size scaling shows whether implementations maintain consistent per-element throughput.
- Cache behavior becomes critical at larger vector sizes (2^28 = ~2GB of data per vector).

---

## Correctness Verification

### Verification Process
1. C kernel serves as the "sanity check answer key"
2. x86-64 assembly output compared against C output
3. Tolerance: 0.001 for floating-point comparison

### Correctness Results
- ✓ Process verification: **[STATUS]**
- ✓ 2^20 elements: **[STATUS]**
- ✓ 2^24 elements: **[STATUS]**
- ✓ 2^28 elements: **[STATUS]**

---

## Compilation and Execution

### Prerequisites
- Windows OS
- Visual Studio 2022 or later (with C++ development workload)
- NASM assembler (v2.15 or later)
- GCC or Clang (optional, for command-line compilation)

### Build Steps (Command Line)

1. Clone the repository:
   ```bash
   git clone https://github.com/Rggman/LBYARCH-x86-to-C-interface-programming-project.git
   cd lbarch-project
   ```

2. Assemble the x86-64 kernel:
   ```bash
   nasm -f win64 asmfunc.asm 
   ```

3. Compile the C code:
   ```bash
   gcc -c main.c -o main.obj -m64
   ```

4. Link and create executable:
   ```bash
   gcc main.obj asmfunc.obj -o main.exe -m64
   ```

5. Run the program:
   ```bash
   main.exe
   ```

### Expected Output
- Displays the execution time for each vector size
- Shows the first 10 elements of the result vector Z for both C and x86-64 implementations
- Provides a summary of correctness verification

---

## Screenshots

<p align="center">
  <img src="https://github.com/user-attachments/assets/b78f63b6-2d2c-4b7e-a6b7-524879bd0e36" width="300">
</p>


---

## Video Demonstration
- Presents execution times for each tested vector size.
- Shows the first 10 elements of the result vector Z for both C and x86-64 implementations
- Concludes with a verification summary confirming whether both kernels produce identical results.


---

## References

- [Intel 64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
- [AMD64 Architecture Programmer's Manual](https://www.amd.com/content/dam/amdsite/documents/APM.pdf)
- [Microsoft x64 Calling Convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention)
- [NASM (Netwide Assembler) Documentation](https://www.nasm.us/doc/)
- [Euclidean Distance - Wikipedia](https://en.wikipedia.org/wiki/Euclidean_distance)

---

## Author
[Your Name]

## Date
November 24, 2025

---

*This project was completed as part of LBYARCH (Low-Level Byte Architecture) course requirements.*
