# main.sh /opt/test 4 az 5 az.az 3kb
# для az максимальное количество = +-244; Для других строк = +-(255-7-len(str))*2;

. check.sh
. ../common/generate.sh
. ../common/create.sh
. ../common/correct.sh

main()
{
    check $@;

    if [[ -f 01.log ]]
    then
	rm 01.log;
    fi
    
    touch 01.log;
    nameLog=01.log; dateLog=$(date +"%d.%m.%y"); sizeLog=$6; pathLog=$(pwd);
    masDir=(); masFile=(); size=$6; path=$1;
    size=$(echo $size | sed "s/kb/K/");
    
    count=0;
    parsenameDefault $3;
    # echo $out;
    # echo ${#out};
    correctName;
    # echo "cn: $out" ;
    generateName $2 $3;
    # echo "gn: ${masDir[@]}";
    # echo "count=$count"
    # backGenerateName $(($2-$count)); # proceed here

    count=0;
    parsenameDefault $5;
    correctName;
    generateName $4 $5;
    # echo "gn: ${masFile[@]}";
    # backGenerateName $(($4-$count));
    # echo "gn: ${masFile[@]}";

    createDir $path $4 1;

}

main $@
