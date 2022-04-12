.data 	
	lista: .word 2 , 0 , 3 , 6, 12 , 5
	size: .word 6

.text 
lw $a0, size 	# carga de tamanho de array (size)
la $a1, lista # Cargamos la direccion de inicio de la lista
jal burbuja


# Definimos la funcion para imprimir el array mas q todo para testing 
printLista: 
	move $t0, $a0 		# seteamos el tamanho de t0 en a0 para poder usarlo en el syscall 
	li $v0, 1 		# seteamos v0 para el syscall
	
	loop: 
		ble $t0, $zero, exit 	# verificamos si el tamanho es 0 
		lw $a0, ($a1)		# recibe un dato en la direccion actual segun el tamanho
		syscall 		# dato de salida	
		
		
				
		addi $a1, $a1, 4 	# incrementamos la direccion actual en 4 bytes
		subi  $t0, $t0, 1 	# restamos al tamanho en 1 (size -1 )
		
		j loop

# a0 tamanho 
# a1 direccion de la posicion 1 del array
burbuja:
	li $t7, 0 		 	# swap. 0 = verdadero, 1 = falso 
	swapL:   
		move $t6, $a0 	 	# Mover el tamanho a t6 para que se pueda operar
		subi $t6, $t6, 1 	# tamanho - 1
		bgtz $t7, printLista 	# si el swp es falso se llama a printLista
		li $t7, 1 		# seteamos el swapp en falso
	loopsize:
		beq $t6, $zero, swapL		# si el tamanho (size) es 0 terminamos el ciclo 
		subi $t5, $t6, 1 		# t5 = t6-1 asi obtenemos el segundo valor
		mul $t0, $t6, 4 		# multiplicamos por 4 bytes para obtener la distancia de a1
		mul $t1, $t5, 4 		# multiplicamos por 4 bytes para obtener la distancia de a1 hasta 1
		add $t2, $t0, $a1 		# anhadimos a la direccion de a1 para obtener la direccion real
		add $t3, $t1, $a1 		# el valor en t2 ahora es el tamanho -1 (size -1) elemento de la lista (lista[size-1])
		lw $t4, ($t2)			# cagar el valor real de t2 en t4
		lw $t5, ($t3)			# cagar el valor real de t3 en t5
		blt $t4, $t5, swapP 		# branch si t2 es menor que t3

		subi $t6, $t6, 1 		# disminuimos el tamanho (size -1)
		j loopsize 			
	
# t5 es el dato menor
# t4 es el dato mayor	
# t3 es la direccion del menor dato
# t2 es la direccion del mayor dato
swapP: 
	sw  $t5, ($t2) 			# se carga el valor de t5 en t2
	sw  $t4, ($t3)			# se carga el valor de t4 en t3
	subi $t6, $t6, 1 		# disminuimos el tamanho (size -1)
	li $t7, 0 			# seteamo swap en verdadero
	j loopsize			# retornamos en 4 al loop


exit: 
	li $v0, 10  			# termina el codigo
	syscall 
