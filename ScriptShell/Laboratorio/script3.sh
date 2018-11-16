for x in *
do
	if [ -d $x ] ; then {
		echo $x
		cd $x
		. script3.sh
		cd ..
	}
	fi
done
