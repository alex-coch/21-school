#!/bin/bash

function folders {
    file_count="$(find $1 -type d| wc -l | awk '{print $1}')"
    echo "Total number of folders (including all nested ones) = $file_count"
    echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
    du -h $1 2>/dev/null | sort -hr | head -5 | awk 'BEGIN{i=1}{printf "%d - %s, %s\n", i, $2, $1; i++}'
    echo "etc up to 5"
}

function files_count {
    all="$(ls -laR $1 | grep "^-" | wc | awk '{print $1}')"
    conf="$(find $1 -type f -name "*.conf" | wc -l)"
    txt="$(find $1 -type f -name "*.txt" | wc -l)"
    exe="$(find $1 -type f -executable | wc -l)"
    log="$(find $1 -type f -name "*.log" | wc -l)"
    arh="$(find $1 -type f -name "*.zip" -o -name "*.7z" -o -name "*.rar" -o -name "*.tar"  -o -name "*.tgz" | wc -l)"
    sl="$(find $1 -type l | wc -l)"
    echo "Total number of files =" $all
    echo "Number of:"
    echo "Configuration files (with the .conf extension) =" $conf
    echo "Text files =" $txt
    echo "Executable files =" $exe
    echo "Log files (with the extension .log) =" $log
    echo "Archive files =" $arh
    echo "Symbolic links =" $arh
}

function files10 {
    echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
    for num in {1..10}
    do
        TOP10=$(find $1 2>/dev/null -type f -exec du -h {} + | sort -rh | head -10 | sed "${num}q;d")
        if ! [[ -z $TOP10 ]];
        then
            echo -n "$num - "
            echo -n "$(echo $TOP10 | awk '{print $2}'), "
            echo -n "$(echo $TOP10 | awk '{print $1}'), "
            echo "$(echo $TOP10 | grep -m 1 -o -E "\.[^/.]+$" | awk -F . '{print $2}')"
        fi
    done
    echo "etc up to 10"
    echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
    for num in {1..10}
    do
      TOP10EXE=$(find $1 2>/dev/null -type f -executable -exec du -h {} + | sort -rh | head -10 | sed "${num}q;d")
      if ! [[ -z $TOP10EXE ]]
      then
          echo -n "$num - "
          echo -n "$(echo $TOP10EXE | awk '{print $2}'), "
          echo -n "$(echo $TOP10EXE | awk '{print $1}'), "

          path=$(echo $TOP10EXE | awk '{print $2}')
          MD5=$(md5sum $path | awk '{print $1}')
          echo "$MD5"
      fi
    done
  echo "etc up to 10"
}

function time_count {
    echo -n "Script execution time (in seconds) = "
    aga="$(( ($(date +%s%N) - $1) ))"
    printf %.0f $(( $aga/1000000000 ))
    if [[ $(( $aga/1000000 )) -lt 100 ]]; then
        echo -n ".0"
        printf %.0f\\n $(( ($aga/1000000) ))
    else
        echo -n "."
        printf %.0f\\n $(( ($aga/1000000-$aga/1000000000*1000) ))
    fi
}
