#/bin/bash

command='bin/hadoop jar contrib/streaming/hadoop-0.20.2-streaming.jar -file /home/experiments/src/mapper.py -mapper /home/experiments/src/mapper.py -file /home/experiments/src/reducer.py -reducer /home/experiments/src/reducer.py'
mv='bin/hadoop fs -mv '
rm='bin/hadoop fs -rmr '
cp='bin/hadoop fs -copyToLocal '
ct='bin/hadoop fs -cat'
function func()
{




for ((i=1;i<$1+1;i++));
do
    echo "Processing $i"
    eval "$command -input $2/* -output tempoutput"
    eval "$rm $2"
    eval "$mv /user/hadoop/tempoutput $2"
done
}
func $1 $2
#eval "$cp $2/* /home/experiments/output/result.txt"
eval "$ct $2/part-* > /home/hadoop/result.txt"
