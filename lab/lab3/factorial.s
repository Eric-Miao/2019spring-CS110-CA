.data
test_input: .word 3 6 7 8

.text
main:
	add t0, x0, x0
	addi t1, x0, 4
	la t2, test_input
main_loop:
	beq t0, t1, main_exit
	slli t3, t0, 2
	add t4, t2, t3
	lw a0, 0(t4) 		#each time of the iteration, a0 stores the new test num

	addi sp, sp, -20 	#store previous t0-t4, so that I can use in the factorial function and thus sp cannot be used
	sw t0, 0(sp)
	sw t1, 4(sp)
	sw t2, 8(sp)
	sw t3, 12(sp)
	sw t4, 16(sp)

	jal ra, factorial

	lw t0, 0(sp) 		#reload the previous t0-t4
	lw t1, 4(sp)
	lw t2, 8(sp)
	lw t3, 12(sp)
	lw t4, 16(sp)
	addi sp, sp, 20

	addi a1, a0, 0 		#this indicate thats my a0 can be used to store the result of the factorial
	addi a0, x0, 1
	ecall 				# Print Result
	addi a1, x0, ' '
	addi a0, x0, 11
	ecall
	
	addi t0, t0, 1
	jal x0, main_loop
main_exit:  
	addi a0, x0, 10
	ecall # Exit

factorial:
	# YOUR CODE HERE
    add t0, a0, x0 		#to store a0 in another place
    addi t1, x0, 1 		#set t1 to be the place store the mid result
loop:
	beq t0, x0, exit	#for(t0=n;t0>0;t0--)
    mul t1, t1, t0		#t1 *= t0
    addi t0, t0, -1
    jal x0, loop
exit:
	add a0, t1, x0
    jr ra
    
