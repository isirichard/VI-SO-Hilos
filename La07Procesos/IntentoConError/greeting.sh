#Nombre: greeting.sh
hour=`date +%H`
if test $hour -lt 12
then
	echo "Buenos dIas, $LOGNAME"
else
	if test $hour -lt 17
	then
		echo "Buenos tardes, $LOGNAME"
	else
		echo "Buenos noches, $LOGNAME"
	fi
fi
