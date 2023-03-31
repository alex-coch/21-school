#!/bin/bash

if [[ -z $1 ]] || [[ $2 ]]; then
    echo "Error: a plenty of or few arguments"
else
    re='[+-]?([0-9]*[.])?[0-9]+' # '[0-9]+$'
    if [[ $1 =~ $re ]]; then
        echo "Error: the argument's a number"
    else
        echo "$1"
    fi
fi
