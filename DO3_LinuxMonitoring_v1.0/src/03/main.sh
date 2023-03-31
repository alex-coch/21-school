#!/bin/bash

error_target=1
param=($1 $2 $3 $4)
if [[ $# != 4 ]]; then
    echo "Error: incorrect number of arguments"
elif [[ $1 == $2 ]] || [[ $3 == $4 ]]; then
    echo "Error: the background color and font settings cannot be the same in the same column"
    echo "Try again - run the script without duplicating 1 with 2 and 3 with 4 parameters."
else
    for i in {0..3..1}
    do
        case ${param[$i]} in
        1)
            param[$i]="7"
            ;;
        2)
            param[$i]="1"
            ;;
        3)
            param[$i]="2"
            ;;
        4)
            param[$i]="6"
            ;;
        5)
            param[$i]="5"
            ;;
        6)
            param[$i]="0"
            ;;
        *)
            echo "Error: wrong color setting: ${param[$i]}"
            error_target=0
            ;;
        esac
    done
    if [[ error_target ]]; then
        bash inf.sh ${param[0]} ${param[1]} ${param[2]} ${param[3]}
    fi
fi
