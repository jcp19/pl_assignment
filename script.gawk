/<quem>.*<\/quem>/ {FS = " e "
                    print $1 "||" $2
		    FS = " "
                    print $0}
