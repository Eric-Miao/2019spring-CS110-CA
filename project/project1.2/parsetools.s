# ShanghaiTech CS110 2019 Project 1.2

#==============================================================================
#                              Project 1-2 Part 3
#                              parsetools.s README
#==============================================================================
# You should implement hex_to_str() and parse_int(). If you want to change test 
# partition, make sure you have totally understood the test case before you 
# changing them.
#==============================================================================

.data
#-------------------------------------------------------
# Test Data - Feel free to add your own after this line
#-------------------------------------------------------
# Used in hex_to_str
hex_str1:   .asciiz "abcdef12\n"
hex_str2:   .asciiz "00034532\n"

# Used in parse_int
hex_str3:   .asciiz "ABCDEF12"
hex_str4:   .asciiz "00034532"
dec_str1:   .asciiz "12345983"
dec_str2:   .asciiz "00023420"

dec_strmy:  .asciiz "2147483647"
hex_strmy:  .asciiz "FFFFFFFF"
#-------------------------------------------------------
# Test Data - Feel free to add your own above this line
#-------------------------------------------------------

test_header_name:   .asciiz "Running test parsetools:\n"
test_hex_to_str_name:   .asciiz "Testing hex_to_str():\n"
test_parse_int_name: .asciiz "Testing parse_int():\n"

newline:   .asciiz "\n"

tc_actual_str:      .asciiz "actual:   "
tc_expected_str:    .asciiz "expected: "
tc_testpass_str:    .asciiz " ...test passes\n"
tc_testfail_str:    .asciiz " ...test FAILS\n"

readline_err_ecall:
    .asciiz "Error in readline: Could not read from file.\n"
readline_err_bufsize:
    .asciiz "Error in readline: Exceeded maximum buffer size.\n"

.globl main
.text   
#------------------------------------------------------------------------------
# function hex_to_str()
#------------------------------------------------------------------------------
# Writes a 32-bit number in hexadecimal format to a string buffer, followed by
# the newline character and the NUL-terminator. The output must contain 8 digits
# so if neccessary put leading 0s in the buffer. Therefore, you should always 
# be writing 10 characters (8 digits, 1 newline, 1 NUL-terminator).
#
# For example:
#  0xabcd1234 => "abcd1234\n\0"
#  0x134565FF => "134565ff\n\0"
#  0x38       => "00000038\n\0"
#
# Write hex letters using lowercase, not uppercase. Do not add the prefix '0x'.
#
# Hint: Consider each group of 4 bits at a time and look at an ASCII table. If 
# you code has more than a few branch statements, you are probably not doing
# things very efficiently.
# Attention: Its a bit different from dec_to_str, not just copy it.
#
# Arguments:
#  a1 = int to write
#  a2 = character buffer to write into
#
# Returns: none
#------------------------------------------------------------------------------
hex_to_str:
    addi sp,sp,-20   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)
    sw ra, 16(sp)

    mv s2,a1        #save a1 in s2

    srli a1,a1,28   #1st character
    jal num_to_ascii
    sb a0,0(a2)

    mv a1,s2        #2nd character
    slli a1,a1,4
    srli a1,a1,28
    jal num_to_ascii
    sb a0,1(a2)

    mv a1,s2        #3th character
    slli a1,a1,8
    srli a1,a1,28
    jal num_to_ascii
    sb a0,2(a2)

    mv a1,s2        #4th character
    slli a1,a1,12
    srli a1,a1,28
    jal num_to_ascii
    sb a0,3(a2)

    mv a1,s2        #5th character
    slli a1,a1,16
    srli a1,a1,28
    jal num_to_ascii
    sb a0,4(a2)

    mv a1,s2        #6th character
    slli a1,a1,20
    srli a1,a1,28
    jal num_to_ascii
    sb a0,5(a2)

    mv a1,s2        #7th character
    slli a1,a1,24
    srli a1,a1,28
    jal num_to_ascii
    sb a0,6(a2)

    mv a1,s2        #8th character
    slli a1,a1,28
    srli a1,a1,28
    jal num_to_ascii
    sb a0,7(a2)
epilogue_hex_to_str:
    li t1,10        # t1 = '\n'
    sb t1,8(a2)     # a2[8] = '\n'
    li t1,0         # t1 = '\0'
    sb t1,9(a2)     # a2[9] = '\0'

    lw s2, 0(sp)        #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    lw ra, 16(sp)
    addi sp,sp,20 

    jr ra           #return to caller

#helper function for hex_to_str
#arguments:
#   a1 = number
#returns: a0 = ascii
num_to_ascii:
    li t0,9             #if t0>9 it is a char
    bge a1,t0,char_num_to_ascii

    addi a0,a1,48      #number -> ascii number 
    j number_num_to_ascii
char_num_to_ascii:
    addi a0,a1,87      #number -> ascii char 

number_num_to_ascii:
    jr ra
#------------------------------------------------------------------------------
# function parse_int()
#------------------------------------------------------------------------------
# Parses the string as an unsigned integer. The only bases supported are 10 and
# 16. We will assume that the number is valid, and that overflow does not happen.
#
# Arguments: 
#  a1 = string containing a number
#  a2 = base (will be either 10 or 16)
#
# Returns: the number
#------------------------------------------------------------------------------
parse_int:
    addi sp,sp,-20   #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)
    sw ra, 16(sp)

    addi t1,a2,0        #t1 = base
    li a0,0             #default return value 0

loop_parse_int:
    lb s2,0(a1)
    beqz s2,epilogue_parse_int  #end of the string

    li s3,60
    bge s2,s3,char_parse_int

    addi s2,s2,-48      #ascii number -> number
    j number_parse_int

char_parse_int:         #ascii char   -> number
    li s3,95
    bge s2,s3,lower_parse_int   #abcdefg

    addi s2,s2,-55      #ABCDEFG
    j number_parse_int
lower_parse_int:
    addi s2,s2,-87      

number_parse_int:
    mul a0,a0,t1        #prev*base + current
    add a0,a0,s2

    addi a1,a1,1         #move a1 to next char
    j loop_parse_int

epilogue_parse_int:
    lw s2, 0(sp)        #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    lw ra, 16(sp)
    addi sp,sp,20 

    jr ra           #return to caller
#------------------------------------------------------------------------------
# function streq() - paste your implementation here
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
###############################################################################
#                 Sample test cases, BE CAREFUL to change them                       
###############################################################################    
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
# Treats arguments as signed ints
#  a1 = register containing actual result
#  a2 = expected value of register
# CLOBBERS: a2, a1, a0, and t0
#-------------------------------------------
check_int_equals:
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
    
    bne t0, a1, check_int_notequal
    jal print_newline
    la a1, tc_testpass_str
    jal print_str
    j check_int_end
check_int_notequal:
    jal print_newline
    la a1, tc_testfail_str
    jal print_str
check_int_end:    
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
    jal test_parse_int
    
    li a0, 10
    ecall
    
#-------------------------------------------
# Tests hex_to_str()
#-------------------------------------------
test_hex_to_str:
    addi sp, sp, -8
    sw s1, 4(sp)
    sw ra, 0(sp)
    la a1, test_hex_to_str_name
    jal print_str

    li a0, 9
    li a1, 10
    ecall
    mv s1, a0

    li a1, 2882400018
    mv a2, s1
    jal hex_to_str
    mv a1, s1
    la a2, hex_str1
    jal check_str_equals
    
    li a1, 214322
    mv a2, s1
    jal hex_to_str
    mv a1, s1
    la a2, hex_str2
    jal check_str_equals
    
    lw ra, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8
    jr ra

#-------------------------------------------
# Tests parse_int()
#-------------------------------------------
test_parse_int:
    addi sp, sp, -4
    sw ra, 0(sp)

    la a1, test_parse_int_name
    jal print_str

    la a1, hex_str3
    li a2, 16
    jal parse_int
    mv a1, a0
    li a2, 0xabcdef12
    jal check_int_equals

    la a1, dec_strmy
    li a2, 10
    jal parse_int
    mv a1, a0
    li a2, 2147483647
    jal check_int_equals

    la a1, hex_strmy
    li a2, 16
    jal parse_int
    mv a1, a0
    li a2, 0xFFFFFFFF
    jal check_int_equals

    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra