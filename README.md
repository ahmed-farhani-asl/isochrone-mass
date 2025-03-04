# Isochrone Mass Calculation Over Time

This repository contains a C++ program that calculates the **total mass** and **remnant mass** of a stellar population over time using isochrone data. The program reads input data from an isochrone file and an initial mass function (IMF) file, processes the data, and outputs the total mass and remnant mass at different time steps.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Usage](#usage)
4. [Input Files](#input-files)
5. [Output Files](#output-files)
6. [Dependencies](#dependencies)

---

## Introduction

The program processes isochrone data to calculate the total mass and remnant mass of a stellar population at different ages. It uses an initial mass function (IMF) to determine the distribution of stellar masses and applies mass loss and remnant formation rules to compute the total mass and remnants over time.

---

## Features

- **Isochrone Data Processing**: Reads and processes isochrone data to extract initial and live masses at different ages.
- **IMF Integration**: Integrates the initial mass function (IMF) to calculate the total mass of the stellar population.
- **Remnant Mass Calculation**: Computes the remnant mass based on stellar evolution rules for different mass ranges.
- **Output Generation**: Generates output files with the total mass and remnant mass at each time step.

---

## Usage

### 1. Compile the code:
```sh
g++ -o isochrone_M isochrone_M(time).cpp -std=c++11 -O3
```

### 2. Prepare the input files:
- isochrone.dat: Contains the isochrone data with columns for age, initial mass, and live mass.
- imf N = 100000.dat: Contains the initial mass function (IMF) data with columns for mass and number of stars.
  
### 3. Run the program:
```sh
./isochrone_M
```

## Input Files

### `isochrone.dat`
This file contains the isochrone data, which can be obtained from the **[Padova Database](http://stev.oapd.inaf.it/cgi-bin/cmd)**.  
It includes the following columns:
- **LogAge**: Logarithm of the age of the stellar population.
- **Mini**: Initial mass of the stars.
- **Live_mass**: Live mass of the stars at the given age.

This file contains the initial mass function (IMF) data with the following columns:

- m: Stellar mass.
- num: Number of stars in the given mass bin.

## Output Files
- Mini_Mlive.dat
This file contains the filtered isochrone data with columns for age, initial mass, and live mass.

- totalMass.dat
This file contains the total mass of the stellar population at each time step.

- totalMass+Remnants.dat
This file contains the total mass plus the remnant mass at each time step.

## Dependencies
C++ Compiler:
The code requires a C++ compiler (e.g., g++).

Standard Libraries:
The program uses the following C++ standard libraries:

- <iostream> for input/output.
- <fstream> for file handling.
- <cmath> for mathematical functions.
