
# Climate Tracker

## Overview
Climate Tracker is a C++ application designed to efficiently manage and analyze large sets of weather data, including precipitation and temperature, for various cities. Utilizing linked lists, the application allows for effective data organization and computation of statistical measures such as monthly averages, minimums, and maximums.

## Features
- **Data Parsing**: Converts raw text input into structured weather and location data.
- **Custom Data Structures**: Uses structs and classes to effectively manage geographic and climatic information.
- **Operator Overloading**: Facilitates data comparison and aggregation.
- **Weather Statistics**: Calculates monthly averages, minimum and maximum values for weather data.

## Installation
To compile and run Climate Tracker, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/alankha/Climate-Tracker.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Climate-Tracker
   ```
3. Compile the source files:
   ```bash
   g++ Prog2.cpp Support.cpp -o ClimateTracker
   ```
4. Run the executable:
   ```bash
   ./ClimateTracker < datafile.csv
   ```
