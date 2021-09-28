#!/bin/bash

time ../build/cache < 120.txt
time ../build/cache < 1k.txt
time ../build/cache < 10k.txt
time ../build/cache < 100k.txt
time ../build/cache < 500k.txt
time ../build/cache < 1kk.txt
