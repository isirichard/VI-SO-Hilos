#!/bin/bash
#Responsable: Iam Contreras Alcazar - ejericio 1 impar

#Verificamos si ingreso los dos argumentos, sino sucede se termina el proceso
if [ $# -ne 2 ]; then
  echo "Ingrese bien los dos argumentos"
  exit 1
fi

#guardamos la direccion y nos dirigimos a ella 
var_direccion=$2/$1
cd $var_direccion

#comprobamos si la direccion es correcta, sino sucede se termina el proceso
if [ -d $var_direccion ]; then
  echo "Directorio correcto, calculando la cantidad de archivos ejecutables"
else
  echo "No exista esa ruta"
  exit 1
fi

var_contador=0  #contador de archivos ejecutables
for i in *      #recorremos todos los archivos
do
  if [ -x $i -a -f $i ]; then #preguntamos si es que son archivos ejecutables(-x) y si son ficheros y no directorios (-f)
    var_contador=$((var_contador+1)) #sumamos el contador
  fi
done
echo "Cantidad de archivos ejecutables: $var_contador" #imprimimos la cantidad archivos ejecutables

