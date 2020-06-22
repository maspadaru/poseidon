#!/bin/bash

################ Build ##########
./poseidon.sh b

################ Run ###########
./poseidon.sh r S samples/simple.ares samples/simple.stream output.txt
cat output.txt

#./poseidon.sh r S samples/steam_generator.ares samples/steam_generator.stream output.txt
#cat output.txt

#./poseidon.sh r R samples/bicycle.ares samples/bicycle.stream output.txt
#cat output.txt

rm output.txt
