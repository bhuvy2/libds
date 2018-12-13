# C Datastructures

[![Build Status](https://travis-ci.com/bhuvy2/libds.svg?branch=master)](https://travis-ci.com/bhuvy2/libds)
[![Coverage Status](https://coveralls.io/repos/github/bhuvy2/libds/badge.svg)](https://coveralls.io/github/bhuvy2/libds)
![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)

_The Datastructures Library C was missing_ - Bhuvy

This library aims to be a dead simple data structures library that helps you build your C programs fast and efficiently without having to worry about efficiency (yet).

## User Guide

Copy the includes directory to a folder findable by your compiler. Then simply link statically with

```
gcc <...> libds.a
```

If you want a version that is thread safe, use the pthread version

```
gcc <...> libds-pthread.a
```

## Developer Guide

Building the project is as simple as.

```
cmake -H. -Bbuild 
cmake --build build -- -j3
```

## Testing Guide

You will need libcheck, on ubuntu you should be able to get this with

```console
sudo apt install check
```

Then you need to go into the test folder and run the cmake command once again
