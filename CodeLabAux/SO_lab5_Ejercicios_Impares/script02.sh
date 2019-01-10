#!/bin/bash
#Responsable: Gerald Zea Quispe - ejercicio2 impar
for i in $*
do
#maximo de sesiones
	max=3
#sesiones por usuario
	num=$(who | grep -c $i)
	echo "sesiones = $num"
	if [ $num -eq 0 ]; then
		echo "Usuario $i no existe"
	elif [ $num -gt 3 ]; then
		echo "Usuario $i ya inicio el maximo de sesiones permitidas"
	else
		echo "usuario $i aun le queda $(($max-$num)) sesiones"
	fi
done
