#!/bin/bash
a_hard_problem(){
	# actually not.
	# this function receives ten arguments
	# and simply returns the sum of them
	ret = 0;
	for number in "$@"
		do
			let ret=ret+number
			echo "ret = \"$ret\""
		done
	return $ret;

}

a_hard_problem 1 2 3 4 5 6 7 8 9 10
# TODO: assign the proper value to the variable `ret`
ret=$?
echo "the sum of numbers is ${ret}"
if [ "${ret}" -eq "55" ];
then
	echo 'Correct!'
else
	echo 'Wrong!'
fi
