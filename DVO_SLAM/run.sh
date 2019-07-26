#!/bin/bash

# pre processing

# get all names
Names=$(ls ~/Tum_dataset)
count=1
# loop over all dataset in names
for entry in $Names; 
do
    if [[ $(echo $entry | cut -d'_' -f 2) == *dataset* ]]
    then
        echo $count
        if [ $count == 1 ]
        then
        # choose a dataset
        dataset=$entry
        echo $entry chosen!
        else
        echo $entry passed!
        fi
        let 'count++'
    else
    echo $entry skipped!
    fi
done

# rum dvo-slam
echo MELODIC_DVO_SLAM_WITH_SE_SYNC RUNNING!

source ./devel/setup.bash

echo using dataset $dataset

roslaunch src/dvo_benchmark/launch/benchmark.launch dataset:=/home/dingyi/Tum_dataset/$dataset

echo DONE WITH $dataset!

echo MELODIC_DVO_SLAM_WITH_SE_SYNC FINISHED!

# call evaluation script
echo

echo EVALUATION BEGIN!

/home/dingyi/Tum_dataset/evaluate_ate.py --verbose --plot /home/dingyi/Tum_dataset/$dataset/plot.png /home/dingyi/Tum_dataset/$dataset/assoc_opt_traj_final.txt /home/dingyi/Tum_dataset/$dataset/groundtruth.txt

display /home/dingyi/Tum_dataset/$dataset/plot.png



