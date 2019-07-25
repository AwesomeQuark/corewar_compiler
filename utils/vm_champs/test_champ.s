.name "The knights who say ni"
.comment "Ni !"


init:
	ld		%4, r5				#addresse du live
	ld		%18, r6				#adresse du jmp
	ld		%8, r7				#addresse du nb player
	ld		%14, r9				#addresse du ld #1
	ld		%11, r10			#addresse di ld #2
	ld		%25, r8				#valeur de l'increment
start:
	ld		%1, r2				#chargement live
	sti		r2, %:after, r5		#ecriture live
	ld		%15, r2				#chargement ld #1
	sti		r2, %:after, r9		#ecriture ld #1
	ld		%42991616, r2		#chargement ld #2
	sti		r2, %:after, r10	#ecriture ld #2
	ld		%655355, r2			#chargement zjmp
	sti		r2, %:after,r6		#ecriture zjmp
	sti		r1, %:after, r7		#ecriture nb player
	fork	%:after				#lancement du process zombie
increment:
	add		r5, r8, r5
	add		r6, r8, r6
	add		r7, r8, r7
	add		r9, r8, r9
	add		r10, r8, r10
	ld		%0, r15				#carry = 1
	zjmp	%:start				#retour
after:
