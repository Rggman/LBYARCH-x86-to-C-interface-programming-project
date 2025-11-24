# LBYARCH-x86-to-C-interface-programming-project
## Output

<p align="center">
  <img src="https://github.com/user-attachments/assets/b78f63b6-2d2c-4b7e-a6b7-524879bd0e36" width="300">
</p>

## Analysis

The results clearly show that the x86-64 assembly kernel consistently outperforms the C kernel for all the vector sizes. This performance gap is to be expected because the assembly version uses instructions and registers that have less instruction overhead and allows more efficiency in performance. Additionally, Assembly is a lower-level language, so it gives you direct control over every register and instruction. Because you can write exactly what the CPU needs without having to add unnecessary extra instructions, you remove the additional tasks that C normally adds. It can also be observed that as vector size increases, the program becomes more memory-bound, or the memory becomes the bottleneck simply because RAM is slower than a CPU.
