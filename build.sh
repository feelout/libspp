#!/bin/sh
make clean && make && sudo make remove && sudo make install
cd Tests
make clean && make
