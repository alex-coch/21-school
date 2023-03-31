#!/bin/bash

begin_time=$(date +%s%N)

if [[ $# == 1 ]]; then
    if [[ "${1: -1}" != "/" || -z $(find $1) ]]; then
        echo "Error: incorrect path"
    else
        source inf.sh
        folders $1
        files_count $1
        files10 $1
        time_count $begin_time
    fi
else
    echo "Error: incorrect number of arguments"
fi
