Experimental Sorting Methods Benchmark
This repository contains a high-precision experimental benchmarking suite designed to evaluate and visualize the real-world performance of fundamental sorting algorithms.

Instead of relying purely on theoretical Big-O notation, this project measures exact execution times (down to the nanosecond) across different array sizes and initial data distributions. The system consists of a bare-metal C execution engine for data generation and sorting, paired with a Python visualization script that renders the results into academic-quality charts.

Features
8 Sorting Algorithms: Bubble, Insertion, Selection, Merge, Quick (Median-of-Three), Heap, Counting, and Radix Sort.

5 Data Distributions: Evaluates algorithmic adaptability by testing against arrays that are Random, Sorted, Reverse Sorted, Few Unique (heavy duplicates), and Nearly Sorted (5% inversions).

Robust Execution Engine: Written in standard C using clock_gettime(CLOCK_MONOTONIC) for highly accurate benchmarking, immune to system clock adjustments.

Safety Timeouts: Includes a 7.0-second early-exit timeout to prevent the system from hanging indefinitely when testing O(n2) algorithms on massive arrays (e.g., N=100,000).

Automated Visualizations: A Python script that automatically processes the generated results.csv to output six complex graphs, including Log-Log complexity proofs and performance heatmaps.

Prerequisites
To run this experiment on your local machine, you will need:

A C Compiler: GCC or Clang (Standard on most Linux/macOS systems; MinGW for Windows).

Python 3.x: Installed on your system.

Python Libraries: pandas, numpy, matplotlib, and seaborn.

You can install the required Python dependencies by running:

Bash
pip install pandas numpy matplotlib seaborn
How to Run the Experiment
Step 1: Compile and Run the C Benchmark

First, compile the C program. This engine handles all the memory allocation, array generation, and sorting.

Bash
gcc sorting_experiment.c -o sorting_experiment
./sorting_experiment
Note: The program will print its progress to the console. Large arrays (like 50,000 and 100,000 elements) may trigger the timeout on slower algorithms (like Bubble Sort). This is intentional and will be logged correctly.

Once finished, the program will output a file named results.csv containing all the raw timing data.

Step 2: Generate the Visualizations

Once the results.csv file is populated, run the Python script to map the data to visual charts.

Bash
python generate_plots.py
The script will silently generate six .png files directly into your project directory.

Generated Visualizations
Running the Python script produces the following outputs:

fig1_all_algos.png: A standard linear scale line-graph comparing all algorithms on random data.

fig2_fast_algos.png: A zoomed-in view isolating the O(nlogn) and non-comparative algorithms.

fig3_data_order.png: A bar chart demonstrating how initial data configurations (e.g., pre-sorted vs. reversed) impact execution times at N=100,000.

fig4_insertion_sort.png: A specific case study on Insertion Sort's extreme variance depending on the number of initial array inversions.

fig5_log_log_proof.png: A Log-Log scale plot that visually separates the algorithms into straight parallel lines, effectively proving their theoretical polynomial complexity classes.

fig6_heatmap_matrix.png: A heatmap matrix detailing execution times for all algorithms across all data types at N=50,000.

File Structure
sorting_experiment.c: The core C engine containing the sorting logic, timer, and data generators.

generate_plots.py: The Python data science script for rendering the results.

results.csv: The output database containing Size, DataType, Algorithm, and Time_Seconds. (A sample is included in this repository).
