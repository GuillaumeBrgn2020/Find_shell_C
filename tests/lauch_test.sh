#!/bin/bash

cd ..

for i in {1..57}
do
	#./mimou/eval_retrieve_unit.sh $i
	./mimou/eval_setup_unit.sh $i
	#./mimou/eval_tests_unit $i
done