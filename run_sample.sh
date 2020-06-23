#!/bin/bash

################ Build ##########
./poseidon.sh b

################ Run ###########
./poseidon.sh r samples/simple.ares samples/simple.stream ../trident/data/tw output.txt
cat output.txt

#./poseidon.sh r samples/steam_generator.ares samples/steam_generator.stream output.txt
#cat output.txt

#./poseidon.sh r samples/bicycle.ares samples/bicycle.stream output.txt
#cat output.txt

rm output.txt
