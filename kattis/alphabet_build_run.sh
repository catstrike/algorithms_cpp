#! /bin/sh

build_dir=build
data_dir=alphabet.data
executable=alphabet

[ ! -d $build_dir ] && mkdir $build_dir

cd $build_dir

cmake ..
make

cd ..

echo "Testing..."

for test_file in $data_dir/*
do
  cat $test_file | $build_dir/$executable
done