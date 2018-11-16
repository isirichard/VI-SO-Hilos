if [ $# -ne 2 ]; then
	echo "neecsito dos argumentos"
	exit 1
fi

if [ $1 -gt $2 ]; then 
	echo "$1 no puede ser mayor que $2"
	exit 2
fi

for ((i=$1 ; i<$2 ; i++))
do
	#tilde invertida
	mod=`expr $i % 2`
	if [ $mod -ne 0 ]; then
		continue
	fi
	echo " $i es par !!"
done


