# now a system starts
# it first launch the daemon process, which keeps running until all the tasks finish
source daemon.sh 


start_time=`date +'%Y-%m-%d %H:%M:%S'`
start_seconds=$(date --date="$start_time" +%s);

# launch all the tasks
# the original scripts run the tasks in sequence though they are actually independent
# try to run them concurrently thus reduce the waiting time
./task1.sh &
./task2.sh &
./task3.sh &
./task4.sh &

wait

end_time=`date +'%Y-%m-%d %H:%M:%S'`
end_seconds=$(date --date="$end_time" +%s);

runtime=$((end_seconds-start_seconds))
echo "time cost: ${runtime}"
if [ "${runtime}" -gt "15" ];
then
	echo 'Too long time. Unqualified'
else
	echo 'Good job'
fi

# kill the daemon before exiting
kill daemon.sh
