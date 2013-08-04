IFS="
"

SOURCE_DIR=$PWD

BOARD=(Input
DigitalInput
AnalogInput
Output
DigitalOutput
PowerLed)

HARDWARE=(
GenericController
OnOffController
LatchedSwitch
MomentarySwitch
ContinuousController)

MIDI=(
MidiTarget
AbstractControl
SingleActionControl
SimpleControl
UpDownControl
DoubleActionControl
DoubleClickControl
Bank
BankSelector)

TARGET=MidiController
TARGET_DIR=$SOURCE_DIR/..

main(){
	case $1 in
		all)
            echo "Builing the library"
            clean_lib
			make_lib
			;;
		clean)
            echo "Cleaning the library"
			clean_lib
			;;
		*)
			echo "Unsupported option"
	esac
	echo Done
}

make_lib(){
#	Create the library from the source files
	generate_h
	generate_cpp
}

generate_h(){
    KEYWORDS=${TARGET_DIR}/keywords.txt
    TARGET_FILE=${TARGET_DIR}/${TARGET}.h
    
    for CLASSNAME in "${BOARD[@]}"; do
        SOURCE_FILE=$SOURCE_DIR/board/${CLASSNAME}.h
        cat $SOURCE_FILE | grep -v "^#include" >> $TARGET_FILE
        echo ${CLASSNAME} KEYWORD1 >> ${KEYWORDS}
        for FUNC in `grep '(' $SOURCE_FILE | grep -v ${CLASSNAME}`; do
            FUNC=`echo $FUNC | sed -E 's:.*[[:space:]]([[:alnum:]~]+)\(.*:\1:'`
            echo "$FUNC" KEYWORD2"\n" >> ${KEYWORDS}
        done
    done
    
    for CLASSNAME in "${HARDWARE[@]}"; do
        SOURCE_FILE=$SOURCE_DIR/hardware/${CLASSNAME}.h
        cat $SOURCE_FILE | grep -v "^#include" >> $TARGET_FILE
        echo ${CLASSNAME} KEYWORD1 >> ${KEYWORDS}
        for FUNC in `grep '(' $SOURCE_FILE | grep -v ${CLASSNAME}`; do
            FUNC=`echo $FUNC | sed -E 's:.*[[:space:]]([[:alnum:]~]+)\(.*:\1:'`
            echo "$FUNC" KEYWORD2"\n" >> ${KEYWORDS}
        done
    done
    
    for CLASSNAME in "${MIDI[@]}"; do
        SOURCE_FILE=$SOURCE_DIR/midi/${CLASSNAME}.h
        cat $SOURCE_FILE | grep -v "^#include" >> $TARGET_FILE
        echo ${CLASSNAME} KEYWORD1 >> ${KEYWORDS}
        for FUNC in `grep '(' $SOURCE_FILE | grep -v ${CLASSNAME}`; do
            FUNC=`echo $FUNC | sed -E 's:.*[[:space:]]([[:alnum:]~]+)\(.*:\1:'`
            echo "$FUNC" KEYWORD2"\n" >> ${KEYWORDS}
        done
    done
    
    echo "$KEYWORDS generated"
    echo "$TARGET_FILE generated"
}

generate_cpp(){
    TARGET_FILE=${TARGET_DIR}/${TARGET}.cpp
    
    echo "
#include \"WProgram.h\"
#include \"${TARGET}.h\"

    " > $TARGET_FILE
    
    for SOURCE_FILE in `find ${SOURCE_DIR} -type f -name \*.cpp`; do
        cat $SOURCE_FILE | grep -v "^#include" >> $TARGET_FILE
    done
    
    echo "$TARGET_FILE generated"
}

clean_lib(){
#   Remove the library from the system
	rm -f ${TARGET_DIR}/${TARGET}.* ${TARGET_DIR}/keywords.txt 
}

main $*