# 2Q Implementation Cache

This program is the model of 2Q Cache. 

## Installation

Do the following simple steps:

```
git clone https://github.com/Vokerlee/CPP-Course-Intel.git
cd CPP-Course-Intel/1.\ Cache\ \(2Q\)/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## How to launch and use

Don't change your directory after installation and do the following (example):

```
time ./cache < ../tests/100k.txt
```

The first 2 number you are to enter are the `cache size` and the `amount of tests`. Then you should enter all tests' elements (integer numbers). After execution the amount of hits is printed.

For have a log you have a possibility to launch `cache_log` instead of `cache`.

## How to generate tests

In case you want to generate your own tests, change `tests/main.cpp` files, build project again and launch `./cache_test`.