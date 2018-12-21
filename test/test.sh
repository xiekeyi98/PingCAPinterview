#!/bin/bash



cd ..
make
cd test
g++ judger.cpp -O2 -o judger
if [[ ! -f "../bin/main" ]]; then
		echo "Can not find the bin/main!"
		exit -1
else
		echo "Find the bin/main."
fi
let cnt=0;
for i in {1..4}
do
		let cnt+=1;
		echo "Running on $cnt tests."
		# test manual data
		datasize=$(du -m test$i.in | awk '{print $1}');
		echo "the input size is (Mbytes)  : $datasize";
		/usr/bin/time -v ../bin/main test$i.in 1> ans.out 2>tmp.out

		if [ $datasize -lt 1024 ];
		then
				./judger test$i.in ans.out
				if [ $? -ne 0 ];
				then
						echo "****************test is incorrect!*************"
						exit -1;
				else
						echo "test is corrcet"
				fi
		fi
		ans=$(cat tmp.out | grep 'Maximum resident set size (kbytes):' | tr -cd "[0-9]")
		# translate Kb to Mb
		let ans=$ans/1024; # Mb
		echo "Maxmimun resident set size (Mbytes):$ans"
		if [[ $ans -gt 1024 ]];
		then
				echo "******** WARNING! The memory used more than 1GB! **********"
				exit -1;
		fi
done

g++ gen.cpp -O2 -o gen
for i in {1..10}
do
		let cnt+=1;
		echo "Running on $cnt tests."
		# generate the random strings
		echo "generating $i test"
		let size=$i*150
		./gen $size > tmp.in
		echo "$i test generating completed "
		datasize=$(du -m test$i.in | awk '{print $1}');
		echo "the input size is (MByte)  : $datasize";
		# test the random strings
		/usr/bin/time -v ../bin/main tmp.in 1> ans.out 2>tmp.out

		if [ $datasize -lt 1024 ];
		then
				./judger tmp.in ans.out
				if [ $? -ne 0 ];
				then
						echo "****************test is incorrect!*************"
						exit -1;
				else
						echo "test is corrcet"
				fi
		fi
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
rm ./gen
rm ./judger
