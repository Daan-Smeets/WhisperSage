# Side Channel Analysis on PQC Schemes

---

## Overview

WhisperSage is a powerful tool designed for capturing and analyzing power traces from cryptographic devices using the ChipWhisperer platform. It enables researchers and engineers to perform side-channel analysis by automating the collection of power traces and providing advanced statistical methods for detecting vulnerabilities in cryptographic implementations. WhisperSage simplifies the complex process of differential power analysis by offering a streamlined workflow that includes incremental statistics, t-tests, and comprehensive trace management, all within a user-friendly Python environment.

---

## Table of Contents

1. [Features](#features)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [How To Capture Specific Parts](#how-to-capture-specific-parts)
5. [Usage](#usage)

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
- Libraries: `numpy`, `matplotlib`, `scipy`
- ChipWhisperer software and hardware

---

## Installation

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/Daan-Smeets/WhisperSage.git
    cd pqc-sca
    ```

2. **Setup Regular PQM4:**

    Follow the Setup/Installation process of regular [PQM4](https://github.com/mupq/pqm4).

3. **Set Up ChipWhisperer:**

    Follow the [ChipWhisperer Installation Guide](https://chipwhisperer.readthedocs.io/en/latest/installation.html) to install the necessary software and drivers.

4. **Install Required Libraries:**

    ```bash
    pip install numpy matplotlib scipy
    ```

---

## How To Capture Specific Parts	

1. **Implement Your Algorithm**

    To capture power traces for a specific cryptographic algorithm, the user needs to correctly integrate their algorithm within WhisperSage. The currently implemented cryptographic schemes are stored within the `crypto_kem` and `crypto_sign` directories, following the same structure as the standard PQM4. Place the algorithm in the appropriate directory and adjust the subsequent commands accordingly. Additionally, the algorithm might require modification t properly integrates it with the existing namespaces and functions used by WhisperSage and pqm4. The relevant namespaces can be found at the top of each file of the integrated implementations.  


2. **Selecting Parts to Capture:**

    The `mupq/crypto_kem/test.c` file will be executed when WhisperSage is ran. In this file, there is a FLAG_SWITCH_CASE with a number of flags corresponding to flags set up in the implementation-specific `capture_settings.c/h`. The current setup is valid for the `crypto_kem/kyber768/m4fmasked` implementation. New implementation can re-use these flags. The following is the example for the capture flag "cf_pb". This code block should be placed around the part in the cryptographic impelementation that needs to be captured:
    ```c
    if (cf_pb) {capture_pins_set();}
    
    // Code that should be captured
    
    if (cf_pb) {capture_pins_clear();}
    ```

3. **Compile the Library:**
	
    Run the following command:
    ```bash
    make PLATFORM=[CHIPWHISPERER_PLATFORM] IMPLEMENTATION_PATH=[PATH_TO_IMPLEMENTATION] [PATH_TO_BIN]
    ```
    - `CHIPWHISPERER_PLATFORM`: Must be one of the available ChipWhisperer platforms, see [ChipWhisperer](https://github.com/newaetech/chipwhisperer).
    - `PATH_TO_IMPLEMENTATION`: The path to the main folder of the desired implementation, with underscores instead of forward slashes.
    - `PATH_TO_BIN`: The name of the bin file. This name must follow the same file convention as `PATH_TO_IMPLEMENTATION`, with '_test' added.

    Example for the `m4fmasked` implementation:
    ```bash
    make PLATFORM=cw308t-stm32f3 IMPLEMENTATION_PATH=crypto_kem/kyber768/m4fmasked bin/crypto_kem_kyber768_m4fmasked_test.bin
    ```

4. **Flashing the Library:**
	
    Install `openocd`, then run:
    ```bash
    openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c "program [PATH_TO_BIN] 0x08000000 verify reset exit"
    ```
    - `PATH_TO_BIN`: The path to the bin file, including the file name, with underscores instead of forward slashes, and with '_test' added.

    Example for the `m4fmasked` implementation:
    ```bash
    openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c "program bin/crypto_kem_kyber768_m4fmasked_test.bin 0x08000000 verify reset exit"
    ```

    The file `run_script.sh` in the main folder has steps 4 and 5 for the `m4fmasked` implementation.

---

## Usage

### Specifying Parameters

Before running the Jupyter Notebook file, a few parameters have to be set in `main()`.

```text
- `max_no_traces` is the number of traces that will be captured. A higher number of traces achieves higher accuracy at the cost of increased execution time.

- `total_trace_segments` represents the number of segments into which the `max_no_traces` is split. Segmenting the captured traces helps manage storage usage efficiently, with each segment saved independently to reduce the memory size of individual files.

- `scope.adc.samples` is the number of samples that ChipWhisperer captures per second. This rate determines how finely the power consumption signal is recorded over time. The maximum sampling rate varies depending on the specific ChipWhisperer setup. For example, the ChipWhisperer Lite used in the research has a maximum sampling rate of 24,400 samples per second. If a user sets a sampling rate higher than what their ChipWhisperer setup can handle, a `ChipWhisperer Scope ERROR: Received fewer points than expected` exception is thrown. WhisperSage automatically calculates the number of runs needed to capture the entire trace based on the chosen sampling rate.

- `flags` is the string of flags that are set. Specific flags configure which part of the cryptographic algorithm is captured during execution. These flags link to specific code in the main test file.

- `output_directory` is the name of the directory where the results, including captured traces and t-test outputs, are stored. This organization ensures that all data are easily accessible for further analysis, replication, or review.
```

### Running the Program

Once all parameters are set, the program can start capturing and analyzing power traces. Simply execute the script or run the Jupyter Notebook. The program will:

1. Capture the specified number of traces.
2. Perform statistical analysis (e.g., t-tests) on the captured data.
3. Save the results in the designated output directory.
4. Show the results on the Jupyter Notebook screen.

### Results

The results of the analysis, including captured traces and statistical outputs, are saved in the output directory. Each set of traces is saved in a separate file, organized by trace segment and run. Statistical analysis results, such as t-test values, are also saved, making it easy to review and further analyze the data. A short version is displayed through Jupyter Notebook, showing if any significant leakage was found.
