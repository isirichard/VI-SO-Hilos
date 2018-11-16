#Nombre: shrtMenu.sh
echo "Por favor selecciones C, E o S para"
echo "[C]opiar un archivo"
echo "[E]liminar un archivo"
echo "[S]alir del programa"

read response
case $response in
		C|c) echo "Nombre el archivo a copiar"
		read filename
			echo "Nombre del archivo destino"
			read destfile
				cp $filename $destfile;;
		E|e) echo "Nombre del archivo a eliminar"
		read filename
			rm $filename;;
		*)echo "Salir ahora";;
esac