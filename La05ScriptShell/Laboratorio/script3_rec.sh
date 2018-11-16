#para lograr recursividad existen 2 formas la primera es la resuelta aqui (poner toda la ruta), la 2da es poner : PATH=$PATH:$HOME/scripts

#iterar en cada archivo o directorio de donde me encuentro
for x in *
do
	#tambien muestra los subdirectorios, si hace recursividad.
	if [ -d $x ]; then {
	       	echo $x
		cd $x	
		. $HOME/Documentos/Paulo/SO/sesion05/ejemplo_clase/script3_rec.sh	
		cd ..
	}
	fi
done
