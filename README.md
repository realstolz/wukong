# graph-store

## install boost-with-mpi

### download

http://www.boost.org/doc/libs/1_58_0/doc/html/mpi/getting_started.html

http://www.boost.org/doc/libs/1_58_0/more/getting_started/unix-variants.html#get-boost  

### build
./bootstrap.sh --prefix=/home/sjx/install/boost_1_58_0/boost_1_58_0-install

add following lines in project-config.jam
using mpi ;

./b2 install 

### modify ~/.bashrc

export BOOST_INCLUDE=/home/sjx/install/boost_1_58_0/boost_1_58_0-install/include

export BOOST_LIB=/home/sjx/install/boost_1_58_0/boost_1_58_0-install/lib

export LD_LIBRARY_PATH=$BOOST_LIB:$LD_LIBRARY_PATH 

## Compile
cd tools

make graph_distributed

## Generate data

download UBA1.7 and Linux_file_path_fix from http://swat.cse.lehigh.edu/projects/lubm/

cd uba/uba1.7/src/ ;

javac edu/lehigh/swat/bench/uba/Generator.java 

replace old class files

Setting up Jena

### generate row data first
cd tools

./generate_lubm.sh 100

### use row data to generate id_data and index_data

./generate_ids.sh 100


## data format

XML-format: generated by uba program from LUBM website

NT-format: Jena transfer XML to NT

default-format: generate_ids.sh transfer NT to default 

	id_***.nt  // s p o triples , use id only
	index_ontology  // all type id 
	index_predict  // mapping form  predict id to strings
	index_subject  // mapping form  subject or object id to strings

reduce the memory usage of index_subject

	minimal_index_subject // useful part of index_subject

convert-format: convert_format.out transfer default to convert

	s_***  //load default-format is too slow and hard to parallel
	o_***  








