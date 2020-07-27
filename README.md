# Poseidon - Real-time reasoning on Twitter streams

## Getting Started

### Prerequisites
* C++ compiler compliant with C++17 standard (tested on GCC 7.3.0 and 
Clang 6.0.0)
* CMake (minimum version: 3.7, tested on 3.10)
* Dependencies (can be installed in Ubuntu 18.04 using `apt`): zlib1g-dev git libboost-all-dev liblz4-dev libtbb-dev libsparsehash-dev python3-dev libcurl-dev
* Python dependencies (can be installed using `pip`): tweepy stanford-openie

### Ares
Create a parent directory that will host Ares, Trident and Poseidon. 
Inside this parent directory clone Ares:
```
git clone https://github.com/maspadaru/ares
```

### Trident
In the same parent directory as Ares, clone Trident:
```
git clone https://github.com/karmaresearch/trident

```
Checkout Trident to branch primitives:
```
cd trident
git checkout  primitives
```
Build Trident:
```
mkdir build
cd build
cmake .. -DSPARQL=1 
make
```

### Build Poseidon
In the same directory as Ares and Trident, clone Poseidon:
```
git clone https://github.com/maspadaru/poseidon
```
Build Poseidon:
```
cd poseidon
./poseidon.sh b
```

### Running sample program 
The sample program uses Wikidata as background knowledge.
Therefore, Wikidata triples need to be downloaded and imported into Trident.
A subset of wikidata can be downloaded from this link: https://wdumps.toolforge.org/dump/470
From the link above you can download a file *wdump-470.nt.gz*, containing Wikidata triples
that can be imported in Trident:
```
cd trident/build
./trident load -f wdump-470.nt.gz -i ../data/
```

Poseidon has two components: the *Twitter Stream Preprocessor* 
and the *Reasoner*.
In order to read the Twitter Stream, a configuration file must be created
and Twitter API credentials must be filled in.
```
cd poseidon/twitter
cp config.example config.py
```
Then the Preprocessor can be started by running:
```
python3 main.py
```
Running the Reasoner with the sample program:
```
cd poseidon
./run_sample.sh 
```
The Preprocessor and Reasoner must be run in parallel.



