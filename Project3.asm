.data
	intArr: .space 400	#intArr[100]
	EnterN: .asciiz "Enter number of elements: "
	Invalid: .asciiz "Please enter a valid number: "
	ShowElements: .asciiz "\nElements in the array are: "
	space: .asciiz " "
	SumOfOdd: .asciiz "\nSum of odd numbers in the array: "
.text
main:
	#Input message
	li $v0, 4
	la $a0, EnterN
	syscall
	jal Input
	
	#Output message
	li $v0, 4
	la $a0, ShowElements
	syscall
	jal Output
	
	#Sum message
	li $v0, 4
	la $a0, SumOfOdd
	syscall
	jal sum
	
	
	
	
	
	j exitProgram

	
		
			
					
Input:
	li $v0, 5
	syscall
	move $s0, $v0		#input n
	
whileInvalid:
	bgt $s0, 100, reInput
	ble $s0, $zero, reInput
	j validInput
reInput:
	li $v0, 4
	la $a0, Invalid
	syscall
	
	li $v0, 5
	syscall
	move $s0, $v0		#input n
	
	j whileInvalid
	
validInput:
	mul $s0, $s0, 4
	move $t0, $zero		#int i = 0;
	
whileInput:
	beq $t0, $s0, exitFunc	#if i == n*4 then exit
	
	#Input intArr[i]
	li $v0, 5
	syscall
	move $t9, $v0		#user enter a number t
	
	sw $t9, intArr($t0)	#arr[i] = t
	addi $t0, $t0, 4	#i = i + 4
	j whileInput		#jump back to the while loop


	
	
Output:
	move $t0, $zero	#int i = 0;
whileOutput:
	beq $t0, $s0, exitFunc
	
	lw $t9, intArr($t0)
	
	#Prints current number
	li $v0, 1
	move $a0, $t9
	syscall
	
	#Prints space
	li $v0, 4
	la $a0, space
	syscall
	
	addi $t0, $t0, 4
	j whileOutput
	
	
	
		
sum:
	move $t0, $zero
	move $s1, $zero
whileSum:
	beq $t0, $s0, outputSum
	
	lw $t9, intArr($t0)
	#r = a - n*(a/n)
	
	div $t8, $t9, 2
	mul $t8, $t8, 2
	sub $t8, $t9, $t8

	bne $t8, $zero, odd			#if n % 2 != 0 then sum
	addi $t0, $t0, 4			#else continue
	j whileSum

odd:
	add $s1, $t9, $s1
	addi $t0, $t0, 4
	j whileSum
	
outputSum:
	li $v0, 1
	move $a0, $s1
	syscall
	j exitFunc
	
	
	
	
	
	
	
exitFunc:
	jr $ra

exitProgram:
	li $v0, 10		
	syscall
	
