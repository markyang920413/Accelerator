#!/bin/bash
arr=(1 2 3 4 5 6 7 8 9 10 15 20 25 30)

rm successed.txt

for (( i = 0 ; i < ${#arr[@]} ; i++ )) ; do
j=0
while [ $j -lt 1 ]
do
./mat_mul 1 ${arr[$i]} > test.txt

count=0
while read A B C D ETC
do
    if [ $B = "success!" ]
    then
        echo "success!" 
        count=$(($count+1))
        continue
    fi

    if [ $count -eq 1 ]
    then
        echo $B >> successed.txt 
        count=$(($count+1))
        continue
    fi

    if [ $count -eq 2 ]
    then
        count=0
        echo "${B} ${D}" >> successed.txt
        break
    fi

done < test.txt

#echo $j
j=$(($j+1))
done
echo "We did local_size: ${arr[$i]} , ${j} test"
done

./convert ${j}
exit 0