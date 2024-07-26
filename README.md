# Side Channel Analysis on PQC Schemes

---

## Overview

This repository contains a program designed to perform Side Channel Analysis on Post-Quantum Cryptography schemes. The program leverages the ChipWhisperer platform to capture and analyze power traces.

---

## Table of Contents

1. [Features](#features)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [Usage](#usage)
    - [Importing Libraries](#importing-libraries)
    - [Initializing ChipWhisperer Scope and Target](#initializing-chipwhisperer-scope-and-target)
    - [IncrementalStats Class](#incrementalstats-class)
    - [Statistical Utility Functions](#statistical-utility-functions)
    - [Additional Functions](#additional-functions)
5. [Contributing](#contributing)
6. [License](#license)

---

## Features

- **Power Trace Capture:** Utilize the ChipWhisperer platform to capture power traces from cryptographic devices.
- **Incremental Statistics:** Efficiently maintain and update statistics for large datasets.
- **Statistical Analysis:** Perform statistical tests, including t-tests, to identify potential vulnerabilities.
- **Visualization:** Plot and visualize power traces to identify patterns and anomalies.
- **Data Management:** Save and load results for future analysis.

---

## Requirements

- Python 3.x
- Libraries: `numpy`, `matplotlib`, `scipy`, `json`, `os`
- ChipWhisperer software and hardware

---

## Installation Preparations

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/yourusername/pqc-sca.git
    cd pqc-sca
    ```

2. **Install Required Libraries:**

    ```bash
    pip install numpy matplotlib scipy
    ```

3. **Set Up ChipWhisperer:**

    Follow the [ChipWhisperer Installation Guide](https://chipwhisperer.readthedocs.io/en/latest/installation.html) to install the necessary software and drivers.


## How To Analyse Specific Parts

1. **Selecting Parts to Analyse:**

    The `mupq/crypto_kem/test.c` file is the file that will be executed. In this file, there is a FLAG_SWITCH_CASE with a number of flags corresponding to flags setup in the implementation-specific `capture_settings.c/h`. The current setup if valid for the `crypto_kem/kyber768/m4fmasked` implementation. For other implementations, new flags should be created.
    These flags can be used to selects parts of the implementation for capture, setting up the correct pins, in this way:
    ```
    if (cf_pb) {capture_pins_set();}
    
    // Code that should be captured
    
    if (cf_pb) {capture_pins_clear();}
    ```


2. **Compile the Library:**
	
    First run `make PLATFORM=[CHIPWHISPERER_PLATFORM] IMPLEMENTATION_PATH=[PATH_TO_IMPLEMENTATION] [PATH_TO_BIN]`
    These three variables must follow specific guidlines (the commands are assumed to be ran in the main folder).
    `CHIPWHISPERER_PLATFORM` must be one of the available ChipWhisperer platforms, see [ChipWhisperer](GITHUB LINK).
    `PATH_TO_IMPLEMENTATION` is the path to the main folder of the desired implementation, with underscores instead of forward slashes.
    `PATH_TO_BIN` will be the name of the bin file. This name must also folow the same file convention as the PATH_TO_IMPLEMENTATION, however with '_test' added.
    As an example for the `m4fmasked` implementation: `make PLATFORM=cw308t-stm32f3 IMPLEMENTATION_PATH=crypto_kem/kyber768/m4fmasked bin/crypto_kem_kyber768_m4fmasked_test.bin`

3. **Flashing the Library:**
	
    Install `openocd`
    To flash the `bin` file, run `openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c "[PATH_TO_BIN] 0x08000000 verify reset exit"`
    `CHIPWHISPERER_PLATFORM` must be one of the available ChipWhisperer platforms, see [ChipWhisperer](GITHUB LINK).
    `PATH_TO_IMPLEMENTATION` is the path to the main folder of the desired implementation, with underscores instead of forward slashes.
    `BIN_NAME` will be the name of the bin file. This name must be the path to the bin file (including the file name), with underscores instead of forward slashes, and with '_test' added.
    As an example for the `m4fmasked` implementation: `openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c "program bin/crypto_kem_kyber768_m4fmasked_test.bin 0x08000000 verify reset exit"`
    
    The file `run_script.sh` in the main folder has step 4 and 5 for the `m4fmasked` implementation. 

---

## Usage

### Specifying parameters

    Before running the Jupyter Notebook file, a few parameters have to be set in `mainTest()`.
- `max_no_traces` is the number of traces that will be captured.
- `total_trace_segments` is the number of segments that the max_no_traces will be divided in.
- `folder_name` is the name of the folder that the resulting measurements will be placed in. If the folder does not exist yet, it will be created.
- `flags` is a string of letters corresponding to the cases of the FLAG_SWITCH_CASE in `mupq/crypto_kem/test.c`. Place al the letters in here of all flags that should be set. For example, `flags = "abd"` would set the flags as `case 'a':`, `case 'b':`, and `case 'd':`.

### Importing Libraries

The program begins by importing necessary libraries, including `numpy` for numerical operations, `matplotlib` for plotting, `scipy` for scientific computations, and ChipWhisperer for capturing power traces.

### Initializing ChipWhisperer Scope and Target

The scope and target are initialized to set up the environment for capturing power traces:

- **Scope Initialization:** `scope = cw.scope()` initializes the scope for capturing power traces.
- **Target Setup:** `target = cw.target(scope, cw.targets.SimpleSerial)` sets up the target device using the SimpleSerial protocol.
- **Default Setup:** `scope.default_setup()` applies default settings to the scope.

### IncrementalStats Class

The `IncrementalStats` class maintains and updates statistics incrementally:

- **Initialization:** The constructor initializes the class with attributes `n`, `mean`, `sum_sq`, and `variance`.
- **Adding Traces:** The `add_trace` method adds a new trace, updating the mean and variance.
- **Getting Statistics:** The `get_stats` method returns the current mean and variance.

### Statistical Utility Functions

These functions perform essential statistical operations:

- **`mean(data)`**: Calculates the mean of the data.
- **`variance(data)`**: Calculates the variance of the data.
- **`ttest_ind_2d(sample1, sample2)`**: Performs a two-sample t-test on two-dimensional data.

### Additional Functions

- **`calc_ttest_data(tval_file)`**: Loads precomputed t-values from a file.
- **`run_experiment(scope, target)`**: Captures and processes power traces from the target device.
- **`plot_results(traces, title)`**: Plots captured power traces with a specified title.
- **`save_results(filename, data)`**: Saves processed data to a file.
- **`load_results(filename)`**: Loads previously saved results from a file.


