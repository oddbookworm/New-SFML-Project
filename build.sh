# Assuming the PROJECTS environment variable is set to the parent directory of this root directory

cd $(dirname "$0")

if [[ ! -d "./bld" ]]; then
    mkdir bld
fi

cd bld

cmake ..

make -j8