#!/bin/bash

EXECUTABLE=poseidon

make_poseidon() {
    mkdir -p cmake-build-release
    cd cmake-build-release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make poseidon 
    cd ..
}

run_poseidon () {
    cmake-build-release/$EXECUTABLE $1 $2 $3 $4
}

clean_up () {
    rm -rf cmake-build-release
}

print_help () {
    echo "Usage: laser [b r c h]"
    echo "b: Build Poseidon"
    echo "r: Run Poseidon"
    echo "c: Clean project"
    echo "h: Print help"
    echo " Option [r] requires additional arguments:"
    echo " chase_algorithm=(S/R) stream_file_path [output_file_path]"
    echo " "

}

if [ $# -eq 0 ]; then 
	print_help 
elif [ $1 = "b" ]; then
    make_poseidon
elif [ $1 = "r" ]; then
    run_poseidon "$2" "$3" "$4" "$5"
elif [ $1 = "c" ]; then
    clean_up
elif [ $1 = "h" ]; then
    print_help
else
	print_help
fi




#ln -s cmake-build-release/compile_commands.json
