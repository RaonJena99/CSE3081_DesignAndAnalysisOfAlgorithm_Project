# README - Algorithm Design and Analysis Projects

## Table of Contents
1. [Project 1: Detection of Brightest Area in 2D Image](#project-1)
2. [Project 2: Min Heap-based Priority Queue Implementation](#project-2)
3. [Project 3: Efficient Implementation of Sorting Algorithms](#project-3)
4. [Project 4: Dynamic Programming Practice](#project-4)
5. [Project 5: Minimum Spanning Tree Algorithm Implementation](#project-5)

---

## Project 1: Detection of Brightest Area in 2D Image

### Objective
The goal of this project is to implement and analyze multiple algorithms for detecting the maximum-sum subrectangle in a 2D image. The performance of different algorithms is compared to theoretical time complexity.

### Implemented Algorithms
1. **Algorithm 3** (O(n⁴)) - Brute Force using Summed Area Table
2. **Algorithm 4** (O(n³ log n)) - Using Divide and Conquer for 1D Maximum Subarray
3. **Algorithm 5** (O(n³)) - Using Kadane’s Algorithm for 1D Maximum Subarray

### Input/Output Specifications
- **Input:** `.pgm` image file and an average intensity text file.
- **Output:** Text file containing maximum sum and subrectangle indices.

### Results and Analysis
- Algorithm 3 is inefficient for large images due to O(n⁴) complexity.
- Algorithm 5 is the most efficient with O(n³) complexity.
- Experimental results align with theoretical expectations.

---

## Project 2: Min Heap-based Priority Queue Implementation

### Objective
The goal is to implement a min-heap-based priority queue and correctly modify the `adjust_client_priority` function to update the heap accordingly.

### Implemented Functions
1. **min_heap_adjust_priority:** Adjusts client priority and updates heap structure.
2. **min_heap_insert:** Inserts a new client into the heap.
3. **min_heap_delete:** Removes and returns the client with the highest priority.

### Input/Output Specifications
- **Input:** Client IDs and priority values.
- **Output:** Text files storing updated client priority values.

### Results and Analysis
- The corrected min-heap operations ensure efficient priority updates.
- Experimentation confirms correctness through predefined test cases.

---

## Project 3: Efficient Implementation of Sorting Algorithms

### Objective
To implement multiple sorting algorithms and optimize them to improve performance.

### Implemented Sorting Algorithms
1. **Insertion Sort** - O(n²)
2. **Heap Sort** - O(n log n)
3. **Weird Sort** - Min Heap followed by Insertion Sort
4. **Quick Sort (Classic)** - O(n log n)
5. **Intro Sort** - Quick Sort with Heap Sort fallback
6. **Merge-Insertion Sort** - Merge Sort with small-size optimization

### Experimental Results
| Algorithm | n=2¹⁴ | n=2¹⁵ | n=2¹⁶ | n=2¹⁷ | n=2¹⁸ | n=2¹⁹ | n=2²⁰ |
|-----------|--------|--------|--------|--------|--------|--------|--------|
| Insertion | 202.8ms | 753.6ms | 3.34s | 12.1s | 49.2s | 195.6s | 781.2s |
| Heap | 1.4ms | 3.2ms | 7.7ms | 13.4ms | 30.0ms | 62.7ms | 141.5ms |
| Quick | 1.2ms | 2.5ms | 5.6ms | 11.6ms | 23.9ms | 55.1ms | 110.7ms |

### Conclusion
- **Heap Sort and Quick Sort** performed well for large input sizes.
- **Intro Sort** showed robust performance due to its adaptability.
- **Weird Sort** was inefficient due to unnecessary Min Heap preprocessing.

---

## Project 4: Dynamic Programming Practice

### Objective
To solve two problems using dynamic programming:
1. **Minimal Triangulation:** Find a non-crossing triangulation of a convex polygon that minimizes the total edge length.
2. **Longest Palindromic Subsequence (LPS):** Find the longest subsequence in a string that reads the same forward and backward.

### Implemented Methods
1. **Dynamic Programming with Table Storage** for both problems.
2. **Backtracking for Minimal Triangulation** to reconstruct the solution.
3. **Iterative Table Filling for LPS** to find the optimal subsequence.

### Results
- **Minimal Triangulation:** Optimally computed for polygons with up to 200 vertices.
- **LPS:** Efficiently found longest palindromic subsequences in large strings.
- Both solutions align with O(n³) and O(n²) complexities, respectively.

---

## Project 5: Minimum Spanning Tree Algorithm Implementation

### Objective
To implement Kruskal’s algorithm using a **Min Heap** and **Disjoint Set Union (DSU)** for efficient computation of the Minimum Spanning Tree (MST).

### Implemented Components
1. **MinHeap Class** - O(log E) operations for extracting the minimum edge.
2. **Disjoint Set (Union-Find)** - O(α(V)) efficient set merging.
3. **Kruskal’s Algorithm** - O(E log V) overall complexity.

### Experimental Results
| Graph File | MST Weight | Execution Time (s) | kScanned |
|------------|------------|------------------|----------|
| com-amazon.ungraph | 2,729,670,156 | 0.30s | 334,862 |
| com-dblp.ungraph | 2,747,895,457 | 0.38s | 317,079 |
| com-youtube.ungraph | 14,578,691,475 | 2.13s | 1,134,889 |
| com-lj.ungraph | 28,308,045,762 | 54.7s | 3,997,961 |

### Conclusion
- The implementation of Kruskal’s algorithm aligns well with its expected O(E log V) complexity.
- Performance varies based on graph density, but the results confirm correctness and efficiency.

---

## Summary
Each project successfully demonstrates different algorithmic techniques and optimization strategies. The experimental results consistently align with theoretical expectations, showcasing the efficiency and limitations of various approaches.

