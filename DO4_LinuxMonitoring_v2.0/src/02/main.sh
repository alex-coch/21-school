# main.sh az az.az 3Mb

. check.sh
. ../common/correct.sh
. ../common/generate.sh
. ../common/create.sh

path=$(find / -type d -perm /u=w,g=w ! \( -path "*/bin" -o -path "*/bin/*" -o -path "*/sbin" -o -path "*/sbin/*" \));
freeMemory=$(df / | awk 'NR ==2{printf $4}');



function startScript {
    startDiff=$(date +'%s%N');
    startLog=$(date +'%Y-%m-%d %H:%M:%S');
    echo "Время начала работы скрипта: $startLog" >> $pathLog/$nameLog;
    echo "Время начала работы скрипта: $startLog";
}

function stopScript {
    endDiff=$(date +'%s%N');
    enfLog=$(date +'%Y-%m-%d %H:%M:%S');
    echo "Время окончания работы скрипта: $enfLog" >> $pathLog/$nameLog;
    echo "Время окончания работы скрипта: $enfLog";
    DIFF=$((( $endDiff - $startDiff ) / 100000000 ));
    echo "Общее время работы скрипта: $(( $DIFF / 10 )).$(( $DIFF % 10 ))" >> $pathLog/$nameLog;
    echo "Общее время работы скрипта: $(( $DIFF / 10 )).$(( $DIFF % 10 ))"
}

main()
{   
    check $@

    if [[ -f 02.log ]]
    then
	    rm 02.log;
    fi

    touch 02.log;
    nameLog=02.log; dateLog=$(date +"%d.%m.%y"); sizeLog=$3; pathLog=$(pwd); masCountIndex=0;
    masDir=(); masFile=(); masCount=(); size=$3;
    startScript;
    size=$(echo $size | sed "s/Mb/M/");
    count=0;
    parsenameDefault $1;
    correctName;
    generateName 100 $1; 

    count=0;
    parsenameDefault $2;
    correctName;
    len2=${#out};
    let "maxFile=255-$len2";
    generateName $maxFile $2;

    # path=$(pwd); path_test='/test.2'; path=$path$path_test; 
    for k in $path
    do
        for((j=0; $j<10; j=$(($j+1)))) # 100
        do
            let "countFile=$RANDOM%$maxFile";
            createDir $k $countFile 2;
        done
    done

    stopScript;
}


main $@
