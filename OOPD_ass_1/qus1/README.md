# Real Estate LTCG Tax Calculation

## Overview

This project calculates Long-Term Capital Gains (LTCG) taxes for real estate investments based on inflation-adjusted tax schemes. The project includes:

1. **Traditional LTCG Calculation** - Calculates LTCG with inflation adjustment and a 20% tax rate.

## Files Included

- `RealEstateLTCG.h`: Header file containing class definitions for inflation rates, property growth rates, and real estate investments.
- `RealEstateLTCG.cpp`: Implementation file containing the logic for reading CSV data and computing LTCG.
- `main.cpp`: Main file that takes user input and outputs the LTCG tax calculations.
- `Makefile`: Build file to compile the source code into executables.
- `inflation_growth.csv`: CSV file containing inflation and property growth rate data (example format provided below).

## Building the Project

To build the project, use the provided `Makefile` to compile the source code into executables. The `Makefile` generates two versions of the binary: one for debugging and one optimized for execution.

### Commands

1. **Build**
   ```bash
   make
2. **Run Debug Version**
   ```bash
   ./realestate_ltcg_debug
3. **Run Optimized Version**
   ```bash
   ./realestate_ltcg_opt

## CSV File Format

The inflation_growth.csv file should be formatted as follows:
```yaml
Year, Growth Rate, Inflation Rate
2001, 5.0, 4.0
2002, 5.2, 4.1
...
2030, 6.0, 5.5

