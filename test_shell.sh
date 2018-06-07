#!/bin/bash 
echo "inicico do script de testes"
echo "testes padrao"

COUNTER=0
python3 test.py -g
while [  $COUNTER -lt 10 ]; do
	./main s "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"
	python3 test.py -cg
	let COUNTER=COUNTER+1
	echo $i
done

COUNTER=0
#python3 test.py -g
while [  $COUNTER -lt 10 ]; do
	./main o "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"
	python3 test.py -cg
	let COUNTER=COUNTER+1
	echo $i
done

COUNTER=0
#python3 test.py -g
while [  $COUNTER -lt 10 ]; do
	./main p "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"
	python3 test.py -cg
	let COUNTER=COUNTER+1
	echo $i
done

echo ""
echo "testes mais aleatorios"
echo ""

COUNTER=0
python3 test.py -z
while [  $COUNTER -lt 10 ]; do
	./main s "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"
	python3 test.py -c
	python3 test.py -z
	let COUNTER=COUNTER+1
	echo $i
done

COUNTER=0
python3 test.py -z
while [  $COUNTER -lt 10 ]; do
	./main o "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"
	python3 test.py -c
	python3 test.py -z
	let COUNTER=COUNTER+1
	echo $i
done

COUNTER=0
python3 test.py -z
while [  $COUNTER -lt 10 ]; do
	./main p "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"
	python3 test.py -c
	python3 test.py -z
	let COUNTER=COUNTER+1
	echo $i
done

echo "fim do script de testes"
