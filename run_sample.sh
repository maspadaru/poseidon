#!/bin/bash

################ Build ##########
./poseidon.sh b

################ Run ###########

#./poseidon.sh r samples/simple.ares samples/simple.stream ../trident/data/simple output.txt
#cat output.txt

./poseidon.sh r samples/book.ares samples/book.stream ../trident/data/book output.txt
cat output.txt

./poseidon.sh r samples/rdfbook.ares samples/rdfbook.stream ../trident/data/rdfbook output.txt
cat output.txt

rm output.txt






#=============================================
# this is how you load the kb and run test queries:

#./trident load -f ../../poseidon/samples/simple.bgd -i ../data/simple
#./trident query -i ../data/simple -q ../../poseidon/samples/simple.qry

#./trident load -f ../../poseidon/samples/book.bgd -i ../data/book
#./trident query -i ../data/book -q ../../poseidon/samples/book1.qry
#./trident query -i ../data/book -q ../../poseidon/samples/book2.qry


#./trident load -f ../../poseidon/samples/rdfbook.bgd -i ../data/rdfbook
#./trident query -i ../data/rdfbook -q ../../poseidon/samples/rdfbook1.qry
#./trident query -i ../data/rdfbook -q ../../poseidon/samples/rdfbook2.qry
