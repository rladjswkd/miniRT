#!/bin/bash

test_valid_dir=files/valid
test_invalid_dir=files/invalid

gcc -o minirt -g *.c -lm 

for f in "$test_invalid_dir"/*
do
	output="$(./minirt "$f")"
	if [ "$output" != "invalid format" ];
	then
		echo "$f"
	fi
done

for f in "$test_valid_dir"/*
do
	output="$(./minirt "$f")"
	if [ "$output" != "valid format" ];
	then
		echo "$f"
	fi	
done

rm minirt