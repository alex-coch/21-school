function check()
{
    path=$1;
    slash=${path:0:1};
    checkNum='^[0-9]+$';
    checkSize='^[[:digit:]]{1,3}kb$';
    checkSizeNum=$(echo $6 | sed 's/[^0-9]*//g') ; 
    limit=100
    checkDir='^\w{1,7}$'; # '^[a-zA-Z0-9\.]{1,7}$';
    checkFile='^\w{1,7}+(\.[a-zA-Z]{1,3})?$'; 


    if [[ $# -ne 6 ]]
    then
        echo "Неверное количество аргументов";
        exit 1;
    fi

    if ! [[ -d "$1" ]] || ! [[ $slash == "/" ]]
    then
        echo "Либо такого пути нет, либо ты указал относительный путь. Надо указывать полный путь";
        exit 1;
    fi

    if ! [[ $2 =~ $checkNum ]] || ! [[ $4 =~ $checkNum ]]
    then
        echo "Второй и четвертый аргумент дб положительными целыми числами";
        exit 1;
    fi

    if ! [[ $6 =~ $checkSize ]] || (($((checkSizeNum)) > $limit))  
    then
        echo "Размер файла в килобайтах - целое число до 100. Пример: 3kb";
        exit 1;
    fi

    if ! [[ $3 =~ $checkDir ]] || ! [[ $5 =~ $checkFile ]]
    then
        echo "В параметрах 3 и 5 дб буквы, максимальная длина - 7, максимальная длина расширения для файлов - 3";
        exit 1;
    fi
}
