#!/bin/bash

export PATH=$PATH:$1

export CTG=yes

WORK=$(pwd)/work
ENV=$(pwd)/riscv-test-env/p/
ISA=$(pwd)/rv32i/ISA
BC=$(pwd)/rv32i/binary_coding

printf "\nCleaning old files ... \n\n"; 
make clean -C $BC
make clean -C $ISA

mkdir -p work/isa
mkdir -p work/bc


printf "\nRunning spike ... \n\n";

make run -C $ISA

printf "\nRunning binary coding tests ... \n\n";
# BINARY TEST
make run -C $BC

printf "\n\nCompare to reference files ... \n\n";
FAIL=0
RUN=0

for f in $ISA/references/*.reference_output;
do 
    b=$(basename $f)
    RUN=$(($RUN + 1))
    diff $f $WORK/isa/${b//".reference_output"/"_signature.output"} #&> /dev/null
    if [ $? == 0 ]
    then
        echo "$b ... OK"
    else
        echo "$b ... FAIL"
        FAIL=$(($FAIL + 1))
    fi
done

for f in $BC/references/*.reference_output;
do
	b=$(basename $f)
    RUN=$(($RUN + 1))   
    diff $f $WORK/bc/${b//".reference_output"/".dump"} #&> /dev/null
    if [ $? == 0 ]
    then
        echo "$b ... OK"
    else
        echo "$b ... FAIL"
        FAIL=$(($FAIL + 1))
    fi
        
done

if [ $FAIL == 0 ]
then
    echo "--------------------------------"
    echo "OK: $RUN/$RUN"
else
    echo "--------------------------------"
    echo "FAIL: $FAIL/$RUN"
fi
