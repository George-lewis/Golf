# Created with MARS-MIPS
#
# This program draws alternating colored lines
#
# Bitmap Display Configuration:
# - Unit width in pixels: 8					     
# - Unit height in pixels: 8
# - Display width in pixels: 256
# - Display height in pixels: 256
# - Base Address for Display: 0x10008000 ($gp)
#
.data
	base:	.word	0x10008000
.text

	li $t0, 0xff0000	# $t0 stores the red colour code
	li $t1, 0x00ff00	# $t1 stores the green colour code
	li $t2, 0x0000ff	# $t2 stores the blue colour code
	
	lw $t3, base		# Current pos, initialize with base address
	
	li $t4, 0 		# Color counter
	li $t5, 128		# Set up division operand
	
loop:
	bne $t4, 0, green
	sw $t0, ($t3)		# Pain read
	j endpaint		# Done painting

green:
	bne $t4, 1, blue
	sw $t1, ($t3)		# Paint green
	j endpaint

blue:
	sw $t2, ($t3)		# Paint blue
	
endpaint:
	
	addi $t3, $t3, 4	# Increment pixel pointer
	
	div $t3, $t5		# Check if we've begun a new line
	mfhi $t6		# Get remainder
	bne $t6, 0, nochange
	addi $t4, $t4, 1	# Increment color
	
nochange:
	
	bne $t4, 3, cont	# 3 is the highest color value
	
	li $t4, 0		# Reset color

cont:

	bne $t3, 16384, noexit	# Check if we need to exit
	j exit
	
noexit:
	sw $t2, 32($t3)
	j loop

exit:
	li $v0, 10 # terminate the program gracefully
	syscall