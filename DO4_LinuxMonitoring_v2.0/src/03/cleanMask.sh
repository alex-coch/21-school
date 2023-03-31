. notice.sh

function cleanMask() {
    echo "Укажите маску (например az_141122)";
    read out;
    checkMask $out;
    date=$(echo $out | sed -r 's/^[^_]+//');
    date=$(echo $date | sed "s/"_"/"*_"/");
    delete=$(find / -ignore_readdir_race -name "$date" | grep [$out]);      

    notice;
}

function checkMask() {
    checkMask='^[a-zA-Z]{1,255}_([3][0-1]|[0-2][0-9])+$|([.][a-zA-Z]{1,3})+$';

    if ! [[ $1 =~ $checkMask ]]
    then
        echo "Ошибка в маске"
        exit 1;
    fi
}
