# If It Fits Your Macros
A command-line tool for calculating your macros for cutting, maintenance, and bulking.

![TDEE Calculator](./images/tdee-calc.png?s=400&raw=true)

## Donations
If you found this utility useful, please consider making a donation of bitcoin to: **3A5M1m2BNSBgo9V7B8wf6VtWQDMMgp5abZ**

All donations help cover maintenance costs and are much appreciated.

## Command Line Options

    -a, --age          The age in years.
    -H, --height       The height in inches or centimeters.
    -w, --weight       The weight in pounds or kilograms.
    -s, --sex          The sex (male or female).
    -m, --use-metric   The units are metric and not imperial.
    -d, --gym-days     The number of days in a week with weight-training.
    -t, --gym-time     The number of minutes spent per work-out.
    -r, --heart-rate   The average heart rate during work-outs.
    -h, --help         Show program usage.

## Build Instructions

### Ubuntu
1. Install dependencies:
```shell
apt install -y autoconf automake libtool
```
2. Build source code by running:
```shell
make
```
### Mac OS X
1. Install [HomeBrew](http://brew.sh/) by running:
```shell
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
2. Install dependencies:
```shell
brew install automake autoconf libtool
```
3. Build source code by running:
```shell
make
```

