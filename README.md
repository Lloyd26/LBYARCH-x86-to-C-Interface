# [LBYARCH] x86-to-C Interface

## Execution Time Analysis (in milliseconds)

**C Average Run Time (30 runs)**
| **Mode** | $n = 2^{20} (1,048,576)$ | $n = 2^{24} (16,777,216)$ | $n = 2^{28} (268,435,546)$ |
|---|---|---|---|
| **Release** | $0.766667 ms$ | $11.533333 ms$ | $184.466667 ms$ |
| **Debug** | $2.833333 ms$ | $48.800000 ms$ | $840.700000 ms$ |

**ASM Average Run Time (30 runs)**
| **Mode** | $n = 2^{20} (1,048,576)$ | $n = 2^{24} (16,777,216)$ | $n = 2^{28} (268,435,546)$ |
|---|---|---|---|
| **Release** | $1.466667 ms$ | $26.266667 ms$ | $367.966667 ms$ |
| **Debug** | $1.600000 ms$ | $27.366667 ms$ | $368.566667 ms$ |

## Correctness Check
$n = 2^3 (8)$  
$a = 2.0$  
$x = {1.0 , 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}$  
$y = {11.0 , 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0}$  
$z[i] = a * x[i] + y[i]$

| **C Correctness Check** | **ASM Correctness Check** |
|---|---|
| ![C Correctness Check](C%20Correctness%20Check.png) | ![ASM Correctness Check](ASM%20Correctness%20Check.png) |

## Brief Performance Analysis
Our analysis reveals a significant performance advantage for the Assembly (ASM) kernel compared to the C kernel. The ASM kernel achieves up to 2x speed for larger datasets ($n=268,435,546$) in Debug mode. This is likely due to ASM’s ability for finer-grained control over hardware resources, leading to more efficient execution.

However, the data also highlights the significance of the build mode. Both kernels exhibit faster execution times in Release mode compared to Debug mode. Release mode prioritizes performance optimization, and it can introduce a noticeable speed difference, especially for the C kernel. While the ASM kernel shows a slight slowdown in Debug mode. This suggests the optimizations in Release mode might have a large impact on the C compiler’s generated code.

In conclusion, the ASM kernel offers superior performance, but at the cost of development complexity and portability. Release mode unlocks the full performance potential of both kernels, while Debug mode prioritizes ease of debugging at the expense of speed.
