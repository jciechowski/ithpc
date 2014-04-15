#!/bin/bash
for i in {1..5}; do
	numerical_integration -n $i -fun 'cos(x)' -x1 -1 -x2 1
done