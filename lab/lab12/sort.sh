#!/bin/bash
a=(82 14 83 16 80 37 47 87 12 79 9 39 32 99 67 89 54 4 6 12)
presult(){
cnt=0
while((cnt!=${#a[*]}))
do
        echo -e "${a[$cnt]} \c"
        ((cnt++))
done
echo -e "\n"
}
presult
quick_sort(){
	# The entrance function to sort the array `a` from the small to the big
	# -- your codes begin
	# TODO: fill your codes here
	real_sort(){
		if [ "$1" -lt "$2" ]
		then
			local i=$1
			local j=$2
			local x=${a[$i]}
			while [ "$i" -lt "$j" ]
			do
				while [[ "$i" -lt "$j" && "${a[$j]}" -gt "$x" ]]
				do
					((j--))
				done
				if [ "$i" -lt "$j" ]
				then
					a[$i]=${a[$j]}
					presult
					((i++))
				fi	
				while [[ "$i" -lt "$j" && "${a[$i]}" -lt "$x" ]]
                                do
					((i++))
                                done
                                if [ "$i" -lt "$j" ]
                                then
                                        a[$j]=${a[$i]}
					presult
                                	((j--))
				fi

			done
			echo "i=$i to devided"	
			a[$i]=$x
			((i=i-1))
			echo "left sort ($1 $i) ""\$x=$x"
			real_sort $1 $i
			((i=i+2))
			echo "right sort ($i $2) ""\$x=$x"
			real_sort $i $2	
			
		fi
}
	real_sort 0 19
	# -- your codes end
	# Any modification in other lines is NOT allowed.
	echo
}

# invoke the sorting function
quick_sort
presult
# check the correctness
ans=(4 6 9 12 12 14 16 32 37 39 47 54 67 79 80 82 83 87 89 99)
for((i=0;i<20;i++))
{
	if [[ "${a[$i]}" -ne "${ans[$i]}" ]]
	then
		echo "Wrong answer at position $i"
		exit 127
	fi
}
echo 'Correct!'
