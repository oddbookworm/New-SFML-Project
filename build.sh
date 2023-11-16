cd $(dirname "$0")

if [[ ! -d "./bld" ]]; then
    mkdir bld
fi

cd bld

cmake ..

make -j8