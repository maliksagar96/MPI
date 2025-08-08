# 🌟🌟🌟 SIMPLE MPI EXAMPLES 🌟🌟🌟

Welcome to a collection of simple MPI (Message Passing Interface) examples!  
Each example demonstrates basic MPI functionality and comes with well-commented C++ code.

> 📂 You’ll find a **short explanation** for each example below. For in-depth comments and implementation details, refer to the respective `.cpp` files.  
> ⚠️ Spoiler: Not all problems benefit from parallelism – we explore both hits and misses!

---

## 📌 01 - Vector Addition

🧮 **Objective**: Add two vectors using MPI.  
This is the simplest possible example – you won’t find an easier one!

### 🧵 Serial Implementation
Straightforward and blazing fast.

### 📊 MPI Algorithm

1) Master process initializes two input vectors A and B.

2) Master scatters chunks of A and B to all worker processes using MPI_Scatter or MPI_Scatterv.

3) Each process performs vector addition on its chunk.

4) Partial results are gathered using MPI_Gather or MPI_Gatherv to form the final result.


### 🎓 What This Teaches
- Use of `MPI_Scatter`, `MPI_Scatterv`, `MPI_Gather`, and `MPI_Gatherv`.
- Limitations of MPI for light computations.

💡 **Note**: Parallel implementation is **slower** than the serial one due to:
- Overhead of distributing data.
- Vector addition isn't compute-intensive.

👉 For better performance, use **CUDA** instead:  
🔗 [CUDA Vector Addition](https://github.com/maliksagar96/CUDA.git)

---

## 📌 02 - Array Sum

➕ **Objective**: Calculate the sum of an array using MPI.

### 📊 MPI Algorithm
1) Master process initializes the array.

2) Array is split into equal parts using MPI_Scatter.

3) Each process computes the sum of its chunk.

4) All partial sums are reduced to a single value using MPI_Reduce.


### 🎓 What This Teaches
- Use of `MPI_Reduce`.
- Understand performance trade-offs in distributed computing.

⚠️ **Observation**: This MPI version is again **slower** than the serial one due to:
- Data scattering overhead.
- Minimal computation per process.

👉 CUDA is a better fit here too:  
🔗 [CUDA Array Sum](https://github.com/maliksagar96/CUDA.git)

---

## 📌 03 - Matrix Multiplication

🧮 **Objective**: Multiply two matrices in parallel.

### 📊 MPI Algorithm


1) Master process initializes matrices A (NxM) and B (MxP).

2) Matrix B is broadcast to all processes using MPI_Bcast.

3) Matrix A is split row-wise using MPI_Scatter or MPI_Scatterv.

4) Each process computes its portion of the resulting matrix C.

5) Partial results are gathered using MPI_Gather to assemble the full matrix.


### 🎯 What This Teaches
- How to use `MPI_Bcast`, `MPI_Scatter`, and `MPI_Gather` together.
- Parallelism pays off – this implementation can **outperform** the serial version for larger matrices!

---

## 🧠 Summary

| Example              | Key MPI Concepts                         | Parallel Performance |
|----------------------|-------------------------------------------|----------------------|
| Vector Addition       | Scatter, Gather                          | ❌ Slower            |
| Array Sum             | Reduce                                   | ❌ Slower            |
| Matrix Multiplication | Bcast, Scatter, Gather                   | ✅ Faster            |

---

✅ If you're looking for raw performance, explore my [CUDA repository](https://github.com/maliksagar96/CUDA.git) for GPU-accelerated alternatives.
