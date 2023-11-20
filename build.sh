for ARGUMENT in "$@"
do
   KEY=$(echo $ARGUMENT | cut -f1 -d=)

   KEY_LENGTH=${#KEY}
   VALUE="${ARGUMENT:$KEY_LENGTH+1}"

   export "$KEY"="$VALUE"
done

cd $(dirname "$0")

if [[ ! -d "./bld" ]]; then
    mkdir bld
fi

cd bld

if [ -z "$LOG_LEVEL" ]; then
    cmake .. -DLOG_LEVEL=3
else
    cmake .. -DLOG_LEVEL="$LOG_LEVEL"
fi

make -j8

echo "Output exists in $(dirname ${0})/bin"