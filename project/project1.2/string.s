# ShanghaiTech CS110 2019 Project 1.2 

#==============================================================================
#                              Project 1-2 Part 1
#                               String README
#==============================================================================
# In this file you will be implementing some utilities for manipulating strings.
# The functions you need to implement are:
#  - strlen()
#  - strncpy()
#  - copy_of_str()
#  - streq()
#  - dec_to_str()
# Test partition also in this file, if you want to change test partition, 
# make sure you have totally understood the test case before you changing them.
#==============================================================================
.data
newline:    .asciiz "\n"
tab:        .asciiz "\t"

tc_actual_str:      .asciiz "actual:   "
tc_expected_str:    .asciiz "expected: "
tc_testpass_str:    .asciiz " ...test passes\n"
tc_testfail_str:    .asciiz " ...test FAILS\n"

#-------------------------------------------------------
# Test Data - Feel free to add your own after this line
#-------------------------------------------------------
test_str1:      .asciiz "a9bw enijn webb"
test_str2:      .asciiz "a9bw en"
test_str3:      .asciiz ""

test_num1:      .asciiz "4396"
test_num2:      .asciiz "77777777"
test_num3:      .asciiz "1011"
#-------------------------------------------------------
# Test Data - Feel free to add your own above this line
#-------------------------------------------------------

test_header_name:       .asciiz "Running string tests:\n"
test_strlen_name:       .asciiz "Testing strlen():\n"
test_strncpy_name:      .asciiz "Testing strncpy():\n"
test_copy_of_str_name:  .asciiz "Testing copy_of_str():\n"
test_dec_to_str_name:   .asciiz "Testing dec_to_str():\n"

# 20 byte buffer x 5 = 100 byte buffer
test_buffer:    .word 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF
                .word 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF
                .word 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF
                .word 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF
                .word 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF

.globl main
.text
#------------------------------------------------------------------------------
# function streq(), a basic function of this project, implement first.
# And we haven't add any separate test cases of this, but nearly any other 
# test case will use this function, so make sure your implementation correct.
#------------------------------------------------------------------------------
# Arguments:
#  a1 = string 1
#  a2 = string 2
#
# Returns: 0 if string 1 and string 2 are equal, -1 if they are not equal
#------------------------------------------------------------------------------
streq:
    addi sp,sp,-16   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)

    li t2,0         #a1[t2]==a2[t2] t2 for add index i
    li a0,0         #flag a0   -1/0  neq/eq
loop_streq:
    add a1,a1,t2    #a1[t2]
    add a2,a2,t2    #a2[t2]

    lb t3,0(a1)     #t3=a1[t2]
    lb t4,0(a2)     #t4=a2[t2]

    beq t3,t4,eq_streq      #jump to eq_streq if t3==t4
    j neq_streq             #jump to neq_streq if t3!=t4

eq_streq:
    beqz t3,epilogue_streq  #jump out if t3==t4=="\0" with a0==0
    
    li t2,1    # i=1 loop
    j loop_streq    

neq_streq:
    li a0,-1         # neq exit

epilogue_streq:
    lw s2, 0(sp)    #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    addi sp,sp,16  

    jr ra           #return to caller
#------------------------------------------------------------------------------
# function strlen()
#------------------------------------------------------------------------------
# Arguments:
#  a1 = string input
#
# Returns: the length of the string
#------------------------------------------------------------------------------
strlen:
    addi sp,sp,-16   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)

    li t2,0         #a1[t2] t2 for adding index 1
    li a0,0         #counter a0
loop_strlen:
    add a1,a1,t2    #a1[t2] always add 1 after first loop
    
    lb t3,0(a1)     #t3=a1[t2]
    beqz t3,epilogue_strlen

    addi a0,a0,1    #counter++
    li t2,1         #adder = 1
    j loop_strlen    

epilogue_strlen:
    lw s2, 0(sp)    #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    addi sp,sp,16  

    jr ra           #return to caller
#------------------------------------------------------------------------------
# function strncpy()
#------------------------------------------------------------------------------
# Arguments:
#  a1 = pointer to destination array
#  a2 = source string
#  a3 = number of characters to copy
#
# Returns: the destination array
#------------------------------------------------------------------------------
strncpy:
    addi sp,sp,-16   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)

    add a0,zero,a1  #set return addr to dest

    li t2,0         #set index t2=0
loop_strncpy:
    add a1,a1,t2
    add a2,a2,t2
    
    lb t3,0(a2)     #t3=a2[t2]
    sb t3,0(a1)     #a1[t2]=t3

    beqz a3,epilogue_strncpy

    li t2,1         #set index t2=1
    addi a3,a3,-1   #a3--
    j loop_strncpy

epilogue_strncpy:
    lw s2, 0(sp)    #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    addi sp,sp,16  

    jr ra           #return to caller
#------------------------------------------------------------------------------
# function copy_of_str()
#------------------------------------------------------------------------------
# Creates a copy of a string. You will need to use sbrk (ecall 9) to allocate
# space for the string. See wiki for details. strlen() and strncpy() will be 
# helpful for this function. ATTENTION: Be careful of the allocation space.
# Taking a second thought on how large (strlen or strlen + 1) should we allocate.
#
# Arguments:
#   a1 = string to copy
#
# Returns: pointer to the copy of the string
#------------------------------------------------------------------------------
copy_of_str:
    addi sp,sp,-20   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)
    sw ra, 16(sp)

    mv s2,a1        #s2 string to copy

    jal strlen
    mv s3,a0        #s3 = strlen(s2)

    addi s3,s3,1    #s3 = strlen(s2) + 1
    mv a1,s3 
    li a0,9       
    ecall           #allocate (strlen+1)

    mv a1,a0        #a1 dest 
    mv a2,s2        #a2 source
    mv a3,s3        #a3 length ( strlen+1 )
    jal strncpy     #a0 holds the dest addr

epilogue_copy_str:
    lw s2, 0(sp)    #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    lw ra, 16(sp)
    addi sp,sp,20 

    jr ra           #return to caller
#------------------------------------------------------------------------------
# function dec_to_str()
#------------------------------------------------------------------------------
# Convert a number to its unsigned decimal integer string representation, eg.
# 35 => "35", 1024 => "1024". 
#
# Arguments:
#  a1 = int to write
#  a2 = character buffer to write into
#
# Returns: the number of digits written
#------------------------------------------------------------------------------
dec_to_str:
    addi sp,sp,-16   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)

    li a0,0         #number of digits written
    li t2,10        #number 10^n for division
#the algorithm implemented here is to convert positive number
    li t5,10        #number 10

getpow_dec_to_str:  #get maximum bit of a1
    div t3,a1,t2
    beqz t3,anspow_dec_to_str
    mul t2,t2,t5    #t2 = t2*10
    j getpow_dec_to_str

anspow_dec_to_str:
    div t2,t2,t5    # 10^n n for a1's bits

loop_dec_to_str:
    div t3,a1,t2    #t3 = a1/t2  first bit of a1

    addi s2,t3,48   #acsii for number s2
    sb s2,0(a2)     #store s2

    addi a2,a2,1    #move a2 to next position
    addi a0,a0,1    #add number

    mul t3,t3,t2    # first bit of a1 * a1's bit
    sub a1,a1,t3    # get rid of a1's top bit

    div t2,t2,t5    # t2 = t2/10
    beqz a1,epilogue_dec_to_str #jump out if a1==0

    j loop_dec_to_str
epilogue_dec_to_str:
    li t2,0
    sb t2,0(a2)     # put last /0 as string end

    lw s2, 0(sp)    #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    addi sp,sp,16  

    jr ra           #return to caller

###############################################################################
#                 Sample test cases, BE CAREFUL to change them                       
###############################################################################
#==============================================================================
#                              string.s Test Cases
#==============================================================================
#-------------------------------------------
# Prints a newline 
# CLOBBERS: a1 and a0
#-------------------------------------------    
print_newline:
    la a1, newline
    li a0, 4
    ecall
    jr ra

#-------------------------------------------
# Prints the string
#  a1 = label containing address of string
# CLOBBERS: a1 and a0
#-------------------------------------------
print_str:
    li a0, 4
    ecall
    jr ra
    
#-------------------------------------------
# Checks whether the actual result matches the expected result
# Treats arguments as unsigned ints
#  a1 = register containing actual result
#  a2 = expected value of register
# CLOBBERS: a2, a1, a0, and t0
#-------------------------------------------
check_uint_equals:
    addi sp, sp, -4
    sw ra, 0(sp)
    mv t0, a1

    la a1, tc_actual_str
    jal print_str

    mv a1, t0
    li a0, 1
    ecall

    jal print_newline

    la a1, tc_expected_str
    jal print_str

    mv a1, a2
    li a0, 1
    ecall

    bne t0, a1, check_uint_notequal
    jal print_newline
    la a1, tc_testpass_str
    jal print_str
    j check_uint_end
check_uint_notequal:
    jal print_newline
    la a1, tc_testfail_str
    jal print_str 
check_uint_end:
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra
    

#-------------------------------------------
# Checks whether the actual result matches the expected result
# Arguments should be strings
#  a1 = register containing actual result
#  a2 = label to expected string
# CLOBBERS: a2, a1, a0, and t0
#-------------------------------------------
check_str_equals:
    addi sp, sp, -4
    sw ra, 0(sp)
    mv t0, a1

    la a1, tc_actual_str
    jal print_str

    mv a1, t0
    li a0, 4
    ecall

    jal print_newline

    la a1, tc_expected_str
    jal print_str

    mv a1, a2
    li a0, 4
    ecall

    jal print_newline

    mv a1, t0
    jal streq
    bne a0, zero, check_str_notequal
    la a1, tc_testpass_str
    jal print_str
    j check_str_end
check_str_notequal:
    la a1, tc_testfail_str
    jal print_str 
check_str_end:
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra

#-------------------------------------------
# Test driver
#-------------------------------------------
main:
    la a1, test_header_name
    jal print_str
    jal print_newline

    jal test_strlen
    jal print_newline
    
    jal test_strncpy
    jal print_newline
    
    jal test_copy_of_str
    jal print_newline

    jal test_dec_to_str
    
    li a0, 10
    ecall

#-------------------------------------------
# Tests strlen()
#-------------------------------------------
test_strlen:
    addi sp, sp, -4
    sw ra, 0(sp)
    la a1, test_strlen_name
    jal print_str 

    la a1, test_str1
    jal strlen
    mv a1, a0
    li a2, 15
    jal check_uint_equals
    
    la a1, test_str3
    jal strlen
    mv a1, a0
    li a2, 0
    jal check_uint_equals
    
    la a1, test_str2
    jal strlen
    mv a1, a0
    li a2, 7
    jal check_uint_equals
    
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra

#-------------------------------------------
# Tests strncpy()
#-------------------------------------------
test_strncpy:
    addi sp, sp, -4
    sw ra, 0(sp)
    la a1, test_strncpy_name
    jal print_str

    la a1, test_buffer
    la a2, test_str1
    li a3, 16       # note: len + 1
    jal strncpy

    mv a1, a0
    la a2, test_str1
    jal check_str_equals
    
    la a1, test_buffer
    la a2, test_str2
    li a3, 8        # note: len + 1
    jal strncpy

    mv a1, a0
    la a2, test_str2
    jal check_str_equals
    
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra

#-------------------------------------------
# Tests copy_of_str()
#-------------------------------------------
test_copy_of_str:
    addi sp, sp, -12
    sw s1, 8(sp)
    sw s2, 4(sp)
    sw ra, 0(sp)
    la a1, test_copy_of_str_name
    jal print_str

    la a1, test_str1
    jal copy_of_str
    mv s1, a0
    
    mv a1, s1
    la a2, test_str1
    jal check_str_equals
    
    la a1, test_str2
    jal copy_of_str
    mv s2, a0

    mv a1, s2
    la a2, test_str2
    jal check_str_equals
    
    lw s1, 8(sp)
    lw s2, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 12
    jr ra

#-------------------------------------------
# Tests dec_to_str()
#-------------------------------------------
test_dec_to_str:
    addi sp, sp, 4
    sw ra, 0(sp)

    la a1, test_dec_to_str_name
    jal print_str

    li a1, 4396
    la a2, test_buffer
    jal dec_to_str
    la a1, test_buffer
    la a2, test_num1
    jal check_str_equals

    li a1, 77777777
    la a2, test_buffer
    jal dec_to_str
    la a1, test_buffer
    la a2, test_num2
    jal check_str_equals

    li a1, 001011
    la a2, test_buffer
    jal dec_to_str
    la a1, test_buffer
    la a2, test_num3
    jal check_str_equals

    lw ra, 0(sp)
    addi sp, sp, -4
    jr ra