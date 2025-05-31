# Performance Report

## Image Processing Optimization Results

### Test Configuration
- **CPU**: 4-core processor
- **Test Image**: 1280×853 pixels (1.09 MPixel)
- **Threads**: 4 worker threads
- **Gaussian Kernel**: 5×5 (σ=5.0)

### Rotation Performance  
| Operation          | Single-Thread | Multi-Thread | Speedup |
|--------------------|---------------|--------------|---------|
| Clockwise          | 20,627 μs     | 10,806 μs    | 1.91x   |
| Counter-clockwise  | 20,283 μs     | 8,619 μs     | 2.35x   |

**Optimizations**:
- Vertical strip parallelization
- Cache-friendly memory access

### Gaussian Filter  
| Metric             | Single-Thread | Multi-Thread | Speedup |
|--------------------|---------------|--------------|---------|
| Execution Time     | 511,411 μs    | 183,067 μs   | 2.79x   |
| Throughput         | 2.13 MP/s     | 5.96 MP/s    | 2.79x   |

**Key Improvements**:
1. Row-wise parallel processing
2. Optimized boundary handling
3. Reduced memory reallocations

### Summary  
- **Rotations**: 1.9–2.4× faster
- **Gaussian Blur**: 2.8× faster
- **Efficiency**: ~70% strong scaling
