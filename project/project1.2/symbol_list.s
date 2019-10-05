# ShanghaiTech CS110 2019 Project 1.2

#==============================================================================
#                              Project 1-2 Part 2
#                               SymbolList README
#==============================================================================
# In this file you will implement a linked list-based data structure for
# storing symbols. Its purpose is analogous to SymbolTable from Proj1-1, but to
# distinguish it we will call it SymbolList.
#
# Each node in the SymbolList contains a (addr, name) pair. An empty SymbolList
# is simply a pointer to NULL. As (addr, name) pairs are added to a SymbolList,
# new list nodes are dynamically allocated and appended to the front of the list. 
# However, as there is no free() in Venus, you do not need to write a free_list()
# function. You may use the functions in string.s during your implementation. 
# What you should do is paste specified function into corresponding position.
#
# You do not need to perform error checking on duplicate addr or name entries
# in SymbolList, nor do you need to do alignment checking. Don't worry about
# provided addresses being too big.
#
# If SymbolList were to be written in C, each list node would be declared as 
# follows:
#   typedef struct symbollist { 
#       int addr;
#       char* name;
#       struct symbollist* next; 
#   } SymbolList;
#
# You need to write new_node(), symbol_for_addr(), addr_for_symbol() and add_to_list().
# You will find test cases in this file. If you want to change test partition, 
# make sure you have totally understood the test case before you changing them.
#==============================================================================

.data
#-------------------------------------------------------
# Test Data - Feel free to add your own after this line
#-------------------------------------------------------
# Test strings
test_label1:    .asciiz "Label 1"
test_label2:    .asciiz "Label 2"
test_label3:    .asciiz "Label 3"

# Test list
node1:      .word 1234 test_label1 0
node2:      .word 3456 test_label2 node1
node3:      .word 5678 test_label3 node2
#-------------------------------------------------------
# Test Data - Feel free to add your own above this line
#-------------------------------------------------------

test_header_name:   
        .asciiz "Running symbol list tests:\n"
test_symbol_for_addr_name:
        .asciiz "Testing symbol_for_addr():\n"
test_addr_for_symbol_name:
        .asciiz "Testing addr_for_symbol():\n"
test_add_to_list_name:  
        .asciiz "Testing add_to_list():\n"

newline:   .asciiz "\n"
tab:       .asciiz "\t"

tc_actual_str:      .asciiz "actual:   "
tc_expected_str:    .asciiz "expected: "
tc_testpass_str:    .asciiz " ...test passes\n"
tc_testfail_str:    .asciiz " ...test FAILS\n"

.globl main
.text
#------------------------------------------------------------------------------
# function new_node()
#------------------------------------------------------------------------------
# Creates a new uninitialized SymbolList node on heap.
# Arguments: none
# Returns: pointer to a SymbolList node
#------------------------------------------------------------------------------
new_node:   
    li a1,12        #allocate 3*4=12bytes
    li a0,9
    ecall

    mv a2,a0        # a2 pointer to struct

    li t2,0         #init node->int = 0
    sw t2,0(a2)

    addi a2,a2,1    #move to next
    sw t2,0(a2)     # node->name = NULL

    addi a2,a2,1    #move to next
    sw t2,0(a2)     # node->next = NULL

    jr ra
#------------------------------------------------------------------------------
# function symbol_for_addr()
#------------------------------------------------------------------------------
#  Iterates through the SymbolList and searches for an entry with the given addr.
#  If an entry is found, return a pointer to the name. Otherwise return NULL.
#
#  Arguments:
#   a1 = addr to look for
#   a2 = pointer to a SymbolList (NULL indicates empty list)
#
#  Returns: a pointer to the name if found or NULL if not found
#------------------------------------------------------------------------------
symbol_for_addr:
    addi sp,sp,-20      #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)
    sw ra, 16(sp)

    li a0,0             # default a0 == NULL (not found)
    beqz a2,epilogue_symbol_for_addr   #a2 == NULL

loop_symbol_for_addr:
    lw t1,0(a2)         # a2: 0 addr 4 name* 8 next*
    beq a1,t1,found_symbol_for_addr     #jump to found
    j nfound_symbol_for_addr            #jump: not this node

found_symbol_for_addr:
    lw a0,4(a2)                         #set return name* 
    j epilogue_symbol_for_addr          #return

nfound_symbol_for_addr:
    lw a2,8(a2)                         #load next node
    beqz a2,epilogue_symbol_for_addr    #check if next == NULL

    j loop_symbol_for_addr              #loop

epilogue_symbol_for_addr:
    lw s2, 0(sp)        #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    lw ra, 16(sp)
    addi sp,sp,20 

    jr ra           #return to caller

#------------------------------------------------------------------------------
# function addr_for_symbol()
#------------------------------------------------------------------------------
# Iterates through the SymbolList and searches for an entry with the given name.
# If an entry is found, return that addr. Otherwise return -1.
#
# Arguments:
#  a1 = pointer to a SymbolList (NULL indicates empty list)
#  a2 = name to look for
#
# Returns:  addr (int) of symbol if found or -1 if not found
#------------------------------------------------------------------------------
addr_for_symbol:
    addi sp,sp,-20      #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)
    sw ra, 16(sp)

    mv s3,a1             #move a1/a2 -> s3/s2 in order to keep them
    mv s2,a2

    li s5,-1             # default s5 == -1 (not found) s5 is return value
    beqz s3,epilogue_addr_for_symbol   #s3 == NULL

loop_addr_for_symbol:
    lw a1,4(s3)         # s3: 0 addr 4 name* 8 next*
    mv a2,s2            # s2: name to look up
    jal streq           # compare  0/-1 eq/neq

    beqz a0,found_addr_for_symbol       #jump to found
    j nfound_addr_for_symbol            #jump: not this node

found_addr_for_symbol:
    lw s5,0(s3)                         #set return addr
    j epilogue_addr_for_symbol          #return

nfound_addr_for_symbol:
    lw s3,8(s3)                         #load next node
    beqz s3,epilogue_addr_for_symbol    #check if next == NULL

    j loop_addr_for_symbol              #loop

epilogue_addr_for_symbol:
    mv a0,s5            #put return value

    lw s2, 0(sp)        #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    lw ra, 16(sp)
    addi sp,sp,20 

    jr ra           #return to caller

#------------------------------------------------------------------------------
# function add_to_list()
#------------------------------------------------------------------------------
# Adds a (name, addr) pair to the FRONT of the list. You should call new_node()
# to create a new node. You do not need to perform error checking on duplicate 
# addr or name entries in SymbolList, nor do you need to do alignment checking.
#
# As with Project 1-1, you WILL need to create a copy of the string that was
# passed in. copy_of_str() from Part 1 will be useful. After new entry has been
# added to the list, return the new list pointer.
#
# Arguments:
#   a1 = ptr to list (may be NULL)
#   a2 = address of symbol (integer)
#   a3 = pointer to name of symbol (string)
#
# Returns: the new list pointer
#------------------------------------------------------------------------------
add_to_list:    
    addi sp,sp,-20      #prologue to save $s reg
    sw s2, 0(sp)
	sw s3, 4(sp)
	sw s4, 8(sp)
	sw s5, 12(sp)
    sw ra, 16(sp)

    mv s4,a1             #move a1/a2/a3 -> s4/s2/s3 in order to keep them
    mv s2,a2
    mv s3,a3

    li s5,0             # default s5 == NULL, s5 is return value

    jal new_node        #create new node
    mv s5,a0            #s5 = new node
    sw s2,0(s5)         #set addr to node

    mv a1,s3            #copy a piece of name*
    jal copy_of_str
    sw a0,4(s5)         #set name* to node

    sw s4,8(s5)         #set next* to node
epilogue_add_to_list:
    mv a0,s5            #return value = new node

    lw s2, 0(sp)        #epilogue to load %s reg
    lw s3, 4(sp)
	lw s4, 8(sp)
	lw s5, 12(sp)
    lw ra, 16(sp)
    addi sp,sp,20 

    jr ra           #return to caller
###############################################################################
#                 DO NOT MODIFY ANYTHING BELOW THIS POINT                       
###############################################################################
#------------------------------------------------------------------------------
# function print_list() - DO NOT MODIFY THIS FUNCTION
#------------------------------------------------------------------------------
# Arguments:
#  a1 = pointer to a SymbolList (NULL indicates empty list)
#  a2 = print function
#------------------------------------------------------------------------------
print_list:
    addi sp, sp, -12        # Begin print_list
    sw s2, 8(sp)
    sw s1, 4(sp)
    sw ra, 0(sp)
    mv s1, a1
    mv s2, a2
print_list_loop:
    beq s1, zero, print_list_end
    lw a1, 0(s1)
    lw a2, 4(s1)
    jalr s2
    lw s1, 8(s1)
    j print_list_loop
print_list_end:
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 12
    jr ra           # End print_list    

#------------------------------------------------------------------------------
# function print_symbol() - DO NOT MODIFY THIS FUNCTION
#------------------------------------------------------------------------------
# Prints one symbol to standard output.
#
# Arguments:
#  a1 = addr of symbol
#  a2 = name of symbol
#
# Returns: none
#------------------------------------------------------------------------------
print_symbol:
    li a0, 1           # Begin print_symbol()
    ecall
    la a1, tab
    li a0, 4
    ecall
    mv a1, a2
    ecall
    la a1, newline
    ecall
    jr ra           # End print_symbol()

###############################################################################
#                 DO NOT MODIFY ANYTHING ABOVE THIS POINT                       
###############################################################################


#------------------------------------------------------------------------------
# function strlen() - paste your implementation here
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
# function strncpy() - paste your implementation here
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
# function copy_of_str() - paste your implementation here
#------------------------------------------------------------------------------
# Creates a copy of a string. You will need to use sbrk (ecall 9) to allocate
# space for the string. strlen() and strncpy() will be helpful for this function.
# In Venus, to malloc memory use the sbrk ecall (ecall 9). See wiki for details.
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

    la a1, node3
    jal test_symbol_for_addr
    jal print_newline

    la a1, node3
    jal test_addr_for_symbol
    jal print_newline
    
    jal test_add_to_list
    
    li a0, 10
    ecall

#-------------------------------------------
# Tests symbol_for_addr()
# a1 = address of beginning of list
#-------------------------------------------
test_symbol_for_addr:
    addi sp, sp, -8
    sw ra, 0(sp)
    sw a1, 4(sp)
    la a1, test_symbol_for_addr_name
    jal print_str

    li a1, 1234
    lw a2, 4(sp)
    jal symbol_for_addr
    mv a1, a0
    la a2, test_label1
    jal check_str_equals

    lw ra, 0(sp)
    addi sp, sp, 8
    jr ra

#-------------------------------------------
# Tests addr_for_symbol()
# a1 = address of beginning of list
#-------------------------------------------
test_addr_for_symbol:
    addi sp, sp, -12
    sw s1, 8(sp)
    sw a1, 4(sp)
    sw ra, 0(sp)
    la a1, test_addr_for_symbol_name
    jal print_str

    lw a1, 4(sp)
    la a2, test_label1
    jal addr_for_symbol
    mv a1, a0
    li a2, 1234
    jal check_int_equals

    lw ra, 0(sp)
    lw s1, 8(sp)
    addi sp, sp, 12
    jr ra

#-------------------------------------------
# Tests add_to_list()
# a1 = address of beginning of list
#
# Because the print is more complex than
# previous tests, the auto comparison haven't
# been implemented. You should check it yourself.
#-------------------------------------------
test_add_to_list:               # Begin test_add_to_list
    addi sp, sp, -4
    sw ra, 0(sp)
    
    la a1, test_add_to_list_name
    jal print_str
    li a1, 0            
    li a2, 1234
    la a3, test_label1
    jal add_to_list         # Test label 1
    mv a1, a0
    li a2, 3456
    la a3, test_label2
    jal add_to_list         # Test label 2
    mv a1, a0
    li a2, 5678
    la a3, test_label3          
    jal add_to_list         # Test label 3
    
    mv a1, a0               # print your list
    la a2, print_symbol
    jal print_list

    jal print_newline

    la a1, node3            # print expected list
    la a2, print_symbol
    jal print_list

    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra
