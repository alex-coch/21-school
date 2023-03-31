#!/bin/bash

head=$(tput setab $1)$(tput setaf $2)
desc=$(tput setab $3)$(tput setaf $4)
normal=$(tput sgr0)

HOSTNAME="${head}HOSTNAME${normal} = ${desc}$(hostname)${normal}"
echo "$HOSTNAME"
TIMEZONE="${head}TIMEZONE${normal} = ${desc}$(cat /etc/timezone) $(date -u +"%Z") $(date +"%z")${normal}"
echo "$TIMEZONE"
USER="${head}USER${normal} = ${desc}$(whoami)${normal}"
echo "$USER"
OS="${head}OS${normal} = ${desc}$(cat /etc/issue | awk '{printf "%s %s %s", $1, $2, $3}')${normal}"
echo -n "$OS"
DATE="${head}DATE${normal} = ${desc}$(date +"%d %h %Y %H:%M:%S")${normal}"
echo
echo "$DATE"
UPTIME="${head}UPTIME${normal} = ${desc}$(uptime -p | awk '{print $2,$3,$4,$5}')${normal}"
echo "$UPTIME"
UPTIME_SEC="${head}UPTIME_SEC${normal} = ${desc}$(cat /proc/uptime | awk '{print $1}') sec${normal}"
echo "$UPTIME_SEC"
IP="${head}IP${normal} = ${desc}$(hostname -I)${normal}"
echo "$IP"
#echo "${desc}$(ip -4 addr |grep inet | awk '{print $2}' | cut -d "/" -f 1) ${normal}"
MASK="$(ip a | grep -e "global")${normal}"
MASK=${MASK#*/}
MASK=${MASK%% *}
MASK="${head}MASK${normal} = ${desc}$(cat mask.txt | grep -w $MASK | awk '{print $2}')${normal}"
echo "$MASK"
GATEWAY="${head}GATEWAY${normal} = ${desc}$(ip r | grep default | awk '{print $3}')${normal}"
echo "$GATEWAY"
RAM_TOTAL="${head}REM_TOTAL${normal} = ${desc}$(free -m | awk '/Mem:/{printf "%.3f GB", $2/1024}')${normal}"
echo "$RAM_TOTAL"
RAM_USED="${head}REM_USED${normal} = ${desc}$(free -m | awk '/Mem:/{printf "%.3f GB", $3/1024}')${normal}"
echo "$RAM_USED"
RAM_FREE="${head}REM_FREE${normal} = ${desc}$(free -m | awk '/Mem:/{printf "%.3f GB", $4/1024}')${normal}"
echo "$RAM_FREE"
SPACE_ROOT="${head}SPACE_ROOT${normal} = ${desc}$(df /root/ | awk '/\/$/ {printf "%.2f MB", $2/1024}')${normal}"
echo "$SPACE_ROOT"
SPACE_ROOT_USED="${head}SPACE_ROOT_USED${normal} = ${desc}$(df /root/ | awk '/\/$/ {printf "%.2f MB", $3/1024}')${normal}"
echo "$SPACE_ROOT_USED"
SPACE_ROOT_FREE="${head}SPACE_ROOT_FREE${normal} = ${desc}$(df /root/ | awk '/\/$/ {printf "%.2f MB", $4/1024}')${normal}"
echo "$SPACE_ROOT_FREE"
