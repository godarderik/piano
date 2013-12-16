#!/bin/bash
cd /Users/joelnpam/PDK/Piano/src 

########################################
##### Enter the name of the file or ####
##### directory to be sent to device####
##### APP="<name of app file/dir>"  ####
########################################
APP="piano"

########################################
#### Enter the relative path to the ####
#### executable here.		    ####
#### EXEC="<relative path to exec>" ####
########################################
EXEC="piano"

if [ "$APP" == "" ];then
	echo "The application file/directory name is not set. Please edit this script to specify the APP variable."
	exit 1
fi

if [ "$EXEC" == "" ];then
        echo "The executable file name is not set. Please edit this script to specify the EXEC variable."
        exit 1
fi

./buildit_for_device.sh
cp piano /Users/joelnpam/piano
palm-launch -c com.godarderik.piano
palm-package /Users/joelnpam/piano
palm-install ./com.godarderik.piano_1.0.8_all.ipk
palm-launch com.godarderik.piano