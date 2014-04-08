#!/bin/bash
for i in {5..50}; do
	numerical_integration -n $i -fun 'cos(x)' -x1 -1 -x2 1
done