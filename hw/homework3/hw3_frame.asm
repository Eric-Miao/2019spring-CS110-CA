# CS 110 Spring 2019 hw3

 

#========================================================================================

#                              Quick Sort RISC-V

#                                   README

#========================================================================================

# In this file you will be implementing the def_quick_sort and def_partition

# function, which form the most important part of this code.

#

# You should sort a 10-integer array. These arrays was reserved in static

# partition of memory. You can change to any 10 numbers you want to sort for

# testing and we will change them to our test case for grading.

#

# We give you the choice to test your code using predefined array: in line 41.

# You can decomment it and use array to test your code.

#

#

#                               IMPORTANT!!!

# Our asembler will support the following registers:

#

# zero, ra, sp, a0 - a1, a2-a4, t3-t6 and s2-s5

# The name x0 can be used in lieu of zero. Other register numbers

# (eg. x1, x2, etc.) are not supported.

#

# We will manually check whether you use registers properly after the ddl.

# So the grade on your autolab is not the final grade of your homework.

#======================================================================================

 

.data

    space:                  .asciiz  " "                # a space string.

    line:                   .asciiz "\n"                # a newline string.

    colonsp:                .asciiz ": "                # a colon string with space.

    .align                  2                           # make data aligned in word

    size:                   .word  10                   # the size of the array                          

    inputstring:            .asciiz "List need sort: "  # the origin array

    sorted_array_string:    .asciiz "Sorted:         "  # the output array

   

#=================================================     Reserved Array     ===========================================|

    #array:          .word 0 0 0 0 0 0 0 0 0 0           # array to be sorted                                        |

    array:           .word 678 567 456 765 876 987 543 654 684 374  # use this line if you want to test this array    |

#====================================================================================================================|                                 

 

.text

.globl  main

main:

    j receive_values_end           # print the testing array           

 

    receive_values_end:

        li    a0, 4                # 4 = print_string ecall.

        la    a1, inputstring       

        ecall

        la    a1, array

        jal   print                # print user input values

 

    # Set up the main quick_sort call.

    # Arrays are    

    la       a1, array             # a1 adrs of the array

    li       a2, 0                 # left val

    lw       a3, size              # right val

    addi     a3, a3, -1            # make a3 the higher index

    jal      def_quick_sort 

    

    li       a0, 4                 # 4 = print_string ecall.

    la       a1, sorted_array_string  

    ecall

    la       a1, array

    jal      print                  # print out the sorted list

 

    j        exit

 

 

########################################################

####################your code here######################

########################################################

 

# In this part you will implemente quick sort and partition seperately.

# You should learn how to use stack and function call before implemente.

# WARNING: using registers properly or you will get 30% deduction after ddl.

#      50% meaningful comments is needed or you will get 50% deduction after ddl.

 

 

def_quick_sort:

    # your code

    addi    sp,sp,-20

      sw          ra,0(sp)

    sw             s2,4(sp)

    sw             s3,8(sp)

    sw             s4,12(sp)

    sw             s5,16(sp)

   

    add            s2, a2, x0                      #s2 = a2, s2 is now the index of lower boundary. to save a2 for next lower boundary.

    add            s3, a3, x0                      #s3 = a3, s3 is now the index of higher boundary. to save a3 for next higher boundary.

    bge            s2, s3, return                #when s2<s3 goes into the recursive sort, otherwise, return.

    jal              def_partition                #using a2,a3 to call the partition function , and a4 is now holding the partition position returned by the function

    addi    a3, a4, -1                            #get the index of the highest of the array to be sorted

    add     a2, s2, x0

    jal              def_quick_sort                     #sort the lower half between a2 and a3(=a4-1)

    add            a3, s3, x0                      #a3 was changed, so we reload a3 here. a3 = s3

    addi    a2, a4, 1                       #get the index of the lowest of the array to be sorted

    jal              def_quick_sort                     #sort the higher half between a2(=a4+1) and a3

      

    j          return                                 #after two sorts, we return.

   

    return:                                          #return function for the function to exit go back to a upper layer..

      lw           ra,0(sp)

    lw              s2,4(sp)

    lw              s3,8(sp)

    lw              s4,12(sp)

    lw              s5,16(sp)

    addi    sp,sp,20

    jr ra

   

 

def_partition:

    addi    sp,sp,-16

    sw             s2,0(sp)

    sw             s3,4(sp)

    sw             s4,8(sp)

    sw             s5,12(sp)

 

       slli   t3, a3, 2                       #t3 = a3*4 = hi_index*4,

    add            t3,    a1, t3                           #add t3,a1,t3

    lw              s3, 0(t3)                        #now, s3 has the word on the highest position. pivot :=A[hi]

 

    addi    s4, a2, 0                       #int j := lo s4 is now j

    addi    s5, a2, 0                       #t5 := lo , so now s5 is i,

    addi    s2, a3, 0                       #s2=hi, so now s2 is the boundary of loop

    loop:

    beq            s4, s2      loop_exit        #loop while s4(lo)<s2(hi-1)

    slli       t4, s4, 2                        #t4 = s4*4 = j_index*4,

    add            t2, a1, t4                      #t2 is now the memory of A[j]

    lw              t3, 0(t2)                        #t2 = A[j]

    blt              t3, s3 swap                         #if A[j] < pivot then swap

    addi    s4, s4, 1                       #s4++; j++

    jal              x0    loop

   

    swap:

    #######

    #here, I should swap A[i] and A[j], which is t5 and t4

    slli       t5, s5, 2                        #s5 = s5*4 = j*4,

    add            t5,    a1, t5                           #s5 is the memory position of A[i]

    lw              t6, 0(t5)                        #t6=A[i]

    sw             t3,    0(t5)       

    sw             t6, 0(t2)

    #######

    addi    s5, s5, 1                       #i:=i+1

       addi s4, s4, 1                       #t4++; j++

    jal              x0    loop

   

    

       loop_exit:

    ######

    ###here we should swap A[i]A[hi]

    slli       t5, s5, 2                        #s5 = s5*4 = j*4,

    add            t5,    a1, t5                           #s5 is the memory position of A[i]

    lw              t6, 0(t5)                        #t6=A[i]

   

    slli       t3, a3, 2                       #t3 = a3*4 = hi_index*4,

    add            t3,    a1, t3                           #add t3,a1,t3

    lw              s3, 0(t3)                        #now, s3 has the word on the highest position. pivot :=A[hi]

   

    sw             s3, 0(t5)

    sw             t6, 0(t3)

    ######

    ###return i

    add            a4, s5, x0                      #now a4 hold t5 = i, waiting to be returned


    lw              s2,0(sp)

    lw              s3,4(sp)

    lw              s4,8(sp)

    lw              s5,12(sp)

    addi    sp,sp,16

    jr ra

# programs ends

#

exit:

    # your code

    addi           a0, x0, 10

    ecall                     # system call

 

 

###       Printing array

print:

    print_loop_prep:

        mv      t3, a1

        lw      t4, size

        li      t5, 0

    print_loop:

        # your code

        mv         s4, t4

        mv         s5, t5

        in_loop:

        beq        s4, s5, exit_print_loop

        li            a0, 1                     # 1 = print the integer

        slli   t5, s5, 2          # s5 now hold the distance the between the fisrt to the present in memory

        add        t5,    t3, t5              # now that t5 hold the real postition of current

        lw          a1, 0(t5)         # a1 now hold the integer

        ecall                                   # print

        addi       s5, s5, 1         # add by 4 so that we go to the next word.

       

        li     a0, 4              # 4 = print_string ecall.

        la   a1, space       # a space after every integer       

        ecall

       

        j             in_loop

        exit_print_loop:

        mv         a1, t3                    #give back the postion after use to a1

        j             print_end

       

    print_end:

        li      a0, 4

        la      a1, line

        ecall

 

        jr      ra

 

########################################################

####################End of your code####################

########################################################
