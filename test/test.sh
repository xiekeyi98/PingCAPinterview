#!/bin/bash



cd ..
make
cd test

let cnt=0;
for i in {1..3}
do
		let cnt+=1;
		echo "Running on $cnt tests."
		# test manual data
		/usr/bin/time -v ../bin/main test$i.in 1> ans.out 2>tmp.out
		ans=$(cat tmp.out | grep 'Maximum resident set size (kbytes):' | tr -cd "[0-9]")
		# translate Kb to Mb
		let ans=ans/1024; # Mb
		echo "Maxmimun resident set size (Mbytes):$ans"
		if [[ $ans -gt 1024 ]];
		then
				echo "******** WARNING! The memory used more than 1GB! **********"
				exit -1;
		fi
done


tmp="https://www.pingcap.com/"
for i in {1..1000}
do
		let cnt+=1;
		echo "Running on $cnt tests."
		# generate the random strings
		echo "generating $i test"
		for j in {1..1000}
		do
				ran=$(head -n 100 /dev/urandom | sed 's/[^a-Z0-9]//g' | strings -n 10 )
				ran=$tmp$RANDOM$ran
				echo $ran >> tmp.in
		done
		echo "$i test generating completed "
		# test the random strings
		/usr/bin/time -v ../bin/main tmp.in 1> ans.out 2>tmp.out
		ans=$(cat tmp.out | grep 'Maximum resident set size (kbytes):' | tr -cd "[0-9]")
		let ans=ans/1024; # Mb
		echo "Maxmimun resident set size (Mbytes):$ans"
		if [[ $ans -gt 1024 ]];
		then
				echo "******** WARNING! The memory used more than 1GB! **********"
				exit -1;
		fi
		rm tmp.in
done

rm ./tmp.out
rm ./ans.out
rm ./tmp.in
