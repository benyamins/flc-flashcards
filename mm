#!/usr/bin/env bash

function print_help {
    echo Use:
    echo '   mm r <args>  # runs executable'
    echo '   mm <args>    # compiles & runs executable'
}

if [[ "$1" = "h" || "$1" = "" ]]
then
    print_help
fi

if [ "$1" = "r" ]
then
    echo -e "\e[1mOnly Running\e[0m"
    echo ------------
    shift
    ./build/flc "$@"
    exit $?
fi

echo -e "\e[1mCompiling & Running\e[0m"
echo -----------------
make
if [ "$?" = "0" ]
then
    ./build/flc "$@"
fi
exit $?

