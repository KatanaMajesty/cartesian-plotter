#!/bin/bash

cmake -S . -B ./Build/
cd ./Build/
make
./cartesian-plotter