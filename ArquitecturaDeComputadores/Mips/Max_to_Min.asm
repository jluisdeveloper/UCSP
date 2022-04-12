.data
	arr: .space 24
	endl: .asciiz "\n"
.text
	main:
	
	addi $s0, $zero, 7
	addi $s1, $zero, 8
	addi $s2, $zero, 3
	addi $s3, $zero, 2
	addi $s4, $zero, 7
	addi $s5, $zero, 10
	
	sw $s0, arr($a0)
		addi $a0, $a0, 4
	sw $s1, arr($a0)
		addi $a0, $a0, 4
	sw $s2, arr($a0)
		addi $a0, $a0, 4
	sw $s3, arr($a0)
		addi $a0, $a0, 4
	sw $s4, arr($a0)
		addi $a0, $a0, 4
	sw $s5, arr($a0)
	
	addi $a1, $a0, 0	
	addi $a0, $zero, 0
	
	sort:
		beq $a0, $a1, done
		jal max
		lw $t0, arr($a1)
		sw $t0, arr($v0)
		sw $v1, arr($a1)
		addi $a1, $a1, -4
	 	j sort
	done:
		addi $t0, $zero, 
	printP:
		beq $t0, 24, exit
		
		lw $t6, arr($t0)
		
		addi $t0, $t0, 4
		
		#printP
		li $v0, 1
		move $a0, $t6
		syscall
		
		#salto de linea
		li $v0,4
		la $a0, endl
		syscall
		
		j printP
	exit:
		li $v0, 10
		syscall
		
	max:
		lw $t0, arr($a0)	
		addi $v0, $a0,0 	
		lw $v1, arr($a0)
		addi $a0, $a0, 4	
		while:
		lw $t3, arr($a0)
		slt $t1, $t0, $t3
		beq $t1, 0, igual	
		finigual:
		beq $a0, $a1, finmax	
		addi $a0, $a0, 4
		j while
	finmax:
	addi $a0, $zero, 0
	jr $ra
			
	igual:
		lw $t0, arr($a0)
		addi $v0, $zero,0
		addi $v0, $a0,0
		lw $v1, arr($a0)
		j finigual		



