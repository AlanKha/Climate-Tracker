
# Climate Tracker

## Overview
Climate Tracker is a C++ application designed to efficiently manage and analyze large sets of weather data, including precipitation and temperature, for various cities. Utilizing a diverse set of data types, the application allows for effective data organization and computation of statistical measures such as monthly averages, minimums, and maximums.

## Features
- **-rawdata mode**: Takes raw CSV data and organizes it by city.
- **Custom Data Structures**: Uses maps, unordered_maps, sets, lists, and vectors to effectively manage geographic and climatic information.
- **Operator Overloading**: Facilitates data comparison and aggregation.
- **Weather Statistics**: Calculates monthly averages, minimum and maximum values for weather data.
- **Request Data by Geocode or State**: Enters an infinite loop prompting the user to enter a location for data.

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
   g++ Prog1.cpp Support.cpp -o ClimateTracker
   ```
4. Run the executable:
   ```bash
   ./ClimateTracker [-rawdata] datafile.csv
   ```

## Example output

```bash
./ClimateTracker weather_US.csv
print> PDX
------------------------------------------
Portland, Oregon (PDX)
------------------------------------------
Jan:  0.21  3.68  1.28 :  32.0  47.0  40.7
Feb:  0.59  1.51  0.94 :  46.0  51.0  49.0
Mar:  0.51  2.04  1.18 :  47.0  52.0  49.8
Apr:  0.05  1.03  0.47 :  55.0  62.0  58.8
May:  0.00  0.83  0.34 :  59.0  65.0  62.2
Jun:  0.19  0.57  0.36 :  59.0  74.0  66.0
Jul:  0.00  0.35  0.13 :  66.0  73.0  69.0
Aug:  0.00  0.09  0.02 :  68.0  76.0  72.0
Sep:  0.04  0.88  0.42 :  60.0  65.0  63.0
Oct:  0.34  3.27  1.62 :  55.0  58.0  56.4
Nov:  0.22  3.75  1.63 :  49.0  56.0  52.8
Dec:  0.08  1.75  1.03 :  33.0  44.0  37.8
print> 
```

```bash
./ClimateTracker -rawdata weather_TN.csv
------------------------------------------
Bristol/Jhnsn_Cty/Kngsprt, Tennessee (TRI)
------------------------------------------
    1  0.00    34
    1  0.67    37
	...
   12  0.78    41
    1  1.09    43
   ...
------------------------------------------
Nashville, Tennessee (BNA)
------------------------------------------
    1  0.00    39
    1  0.30    41
    ...
   12  2.17    44
    1  1.22    50
```

```bash
./ClimateTracker weather_SE.csv

print> Tennessee
------------------------------------------
Nashville, Tennessee (BNA)
------------------------------------------
Jan:  0.00  1.42  0.56 :  26.0  50.0  39.7
Feb:  0.28  1.79  1.12 :  31.0  50.0  43.5
...

------------------------------------------
Knoxville, Tennessee (TYS)
------------------------------------------
Jan:  0.00  1.45  0.70 :  27.0  46.0  37.3
Feb:  0.14  3.09  1.78 :  29.0  47.0  41.5
...
Dec:  0.64  2.28  1.38 :  41.0  43.0  41.8

print> MEM
------------------------------------------
Memphis, Tennessee (MEM)
------------------------------------------
Jan:  0.00  1.42  0.52 :  32.0  51.0  42.5
Feb:  0.11  2.03  1.39 :  39.0  55.0  47.5
...
Dec:  0.49  2.18  1.62 :  40.0  46.0  43.0
```


