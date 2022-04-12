.data
	grado: .asciiz"Ingresa el grado del polinomio: "
	coeficientes: .asciiz"Ingresa los coeficientes uno por uno: "
	float: .asciiz"Ingresa x en formato float: "
	floatzero: .float 0.0
	floatuno: .float 1.0
	exponente: .word 0
	msgfinal: .asciiz"El resultado final es: "
.text
.globl __start

__start:

li $v0, 4
la $a0, grado
syscall

li $v0, 5
syscall
move $t0, $v0
sw $v0, exponente

add $t0, $t0, 1 
mul $t0, $t0, 32
li $v0, 9
move $a0, $t0
syscall

addi $s0, $v0, 0	
add $s1, $s0, $t0	

addi $t1, $s0, 0  
ingresar_coef:
	beq $t1, $s1, fin_ingresar_coef
	
	li $v0, 4
	la $a0, coeficientes #imprime el texto "Ingresa los coeficientes uno por uno: "
	syscall

	li $v0, 5
	syscall
	move $t0, $v0
	
	sw $t0,0($t1)
	
	addi $t1, $t1, 32
	
	j ingresar_coef

fin_ingresar_coef:
	
lwc1 $f1,floatzero #$f1 = 0.0
lwc1 $f7,floatuno #$f7 = 1.0

li $v0, 4
la $a0, float #imprime el texto "Ingresa x en formato float: "
syscall

li $v0, 6
syscall

add.s $f2, $f0, $f1 #guardo en $f2 el valor de x en float

addi $t0, $s0, 0  #puntero al primer elemento
lw $t1, exponente
mtc1 $t1, $f3
cvt.s.w $f3, $f3 

while:
	beq $t0, $s1, fin_while
	jal exponente_loop
	addi $t1, $t1, -1
	lw $t3, 0($t0) 
	mtc1 $t3, $f5
	cvt.s.w $f5, $f5
	mul.s $f5,$f5,$f4
	add.s $f6, $f6,$f5
	addi $t0, $t0, 32
	j while
fin_while:

exit:
	li $v0, 4
	la $a0, msgfinal
	syscall
	
	li $v0, 2
	mov.s $f12, $f6
	syscall
	
	li $v0, 10
	syscall

exponente_loop:
	addi $t2, $t1, 0 
	add.s $f4, $f2, $f1 #copia de x en $f4 	
	while_exponente:
		beq $t2, 1, fin_while_exponente	
		beq $t2, 0, ultimapotencia1
		mul.s $f4, $f4, $f2
		addi $t2, $t2, -1
		j while_exponente
	fin_while_exponente:
	jr $ra
	ultimapotencia1:
		add.s $f4, $f1, $f7
		j fin_while_exponente

