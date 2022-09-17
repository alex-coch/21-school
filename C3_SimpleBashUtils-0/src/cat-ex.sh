#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
	LEAKS="leaks -atExit --  "
else
	LEAKS="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --trace-children=yes --track-fds=yes  --log-file=valgrind.log "
fi

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="file/bytes.txt"
echo "" > cat_log.txt

for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          $LEAKS ./cat/s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> cat_log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
done


echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"