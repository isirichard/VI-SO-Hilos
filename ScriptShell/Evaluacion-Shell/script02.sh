if [ $# -ne 1 ]; then
	echo "Sólo una dirección"
	exit 1
fi

if [ find $1 | wc -l -lt 1 ]
	echo "No existe directorio"
fi 	


find . -type f -perm 0700 > lst_file:


echo "continua"


