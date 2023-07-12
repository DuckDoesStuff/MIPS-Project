.data
	str1: .asciiz  "Enter a number: "
	outputAdd: .asciiz "\nAddition: "
	outputSub: .asciiz "\nSubtraction: "
	outputMul: .asciiz "\nMultiplication: "
	outputDiv: .asciiz "\nDivision: "
	outputMod: .asciiz "\nModulo: "

.text
	la $a0, str1
	
	# Asking user to input first number
	li $v0, 4
	syscall
	# Enter first num
	li $v0, 5
	syscall
	# Store first num as t0
	move $t0, $v0
	
	
	# Asking user to input second number
	li $v0, 4
	syscall
	# Enter second num
	li $v0, 5
	syscall
	# Store second num as t1
	move $t1, $v0
	
	add $t2, $t0, $t1
	# Output addition answer
	la $a0, outputAdd
	li $v0, 4
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	
	
	sub $t2, $t0, $t1
	# Output subtraction answer
	la $a0, outputSub
	li $v0, 4
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	
	mul $t2, $t0, $t1
	# Output multiplication answer
	la $a0, outputMul
	li $v0, 4
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	
	div $t2, $t0, $t1
	# Output division answer
	la $a0, outputDiv
	li $v0, 4
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	
	div $t2, $t0, $t1#7
	mul $t1, $t1, $t2
	sub $t2, $t0, $t1
	# Output modulo answer
	la $a0, outputMod
	li $v0, 4
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
