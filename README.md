# Lab Report - OpenMP Exercises

This repository contains the source code and related files for the OpenMP exercises. Below you'll find a brief overview of the contents and instructions on how to run the different exercises.

## Overview

- **Exercise 1-5:** Each exercise focuses on different aspects of OpenMP, such as thread management, variable scoping, parallel loops, tasking, and performance measurements.
- **Exercise 3:** In this exercise, the task is to explicitly create parallel tasks by dividing the iteration space (0–50) into segments. This approach demonstrates task creation and scheduling in OpenMP, even though a parallel loop could have been used as well.
- **Reports:** You can find the detailed lab report in both PDF and Markdown formats:
  - [REPORT.pdf](./REPORT.pdf)
  - [REPORT.md](./REPORT.md)

## How to Build and Run

A `run.sh` script is provided to simplify the build process. The script performs the following actions:

- Clears the screen.
- Removes any existing build directory.
- Creates a new build directory.
- Runs CMake and compiles the project.
- Executes the compiled executable for Exercise 3.

Here is the content of the `run.sh` file:

```sh
clear
rm -fr build
mkdir build
cd build
cmake ..
make
# ls
clear
# export OMP_NUM_THREADS=4
./exercice_3
cd ..
```

> **Note:**  
> To run each exercise, you can either modify the `run.sh` file to call the appropriate executable or run the script once and then manually execute the desired compiled project from the build directory.

## Running the Exercises

- **Using the Script:** Simply run `./run.sh` from the repository root to build and execute the default exercise (currently Exercise 3).
- **Manually Running Other Exercises:** After running the script, navigate to the `build` directory and execute the compiled executable corresponding to the exercise you want to run.
