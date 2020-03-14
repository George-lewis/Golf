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
	li $t4, 0 		# Position in line
	li $t5, 0 		# Line count

loop: 				# Painting loop
	li $v0, 3 		# Set up Division operand
	divu $t5, $v0 		# Divide
	mfhi $t6 		# Capture remainder
	bne $t6, 0, blue 	# If $t3 % 3 != 0 then jump to tryblue
	sw $t0, ($t3) 		# Paint red
	j finishpaint 		# Jump over the rest of the paint operations

blue:
	li $v0, 2
	divu $t5, $v0		# Check if line count is multiple of two
	mfhi $t6
	bne $t6, 0, green 	# Jump to trygreen if $t3 % 2 != 0
	sw $t1, ($t3) 		# Paint green
	j finishpaint

green:

	sw $t2, ($t3) 		# Paint blue

finishpaint:

    	# increase counters by 4 bytes
	addiu $t3, $t3, 4
	addiu $t4, $t4, 4
	
	bne $t4, 128, ifline # if $t2 is 128, then we're done the line, otherwise jump to ifline
	li $t4, 0 # set line pos back to 0
	addiu $t5, $t5, 1 # increment line count 
ifline:
	bne $t5, 128, continue # if line count is 128 our program exits
	j exit
continue:
	j loop
	
exit:
	li $v0, 10 # terminate the program gracefully
	syscall
