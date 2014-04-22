#!/bin/bash
rm pomiary/*
for i in {5..500}; do
	numerical_integration -n $i -fun 'cos(x)' -x1 -1 -x2 1 -p 128
done