#!/bin/bash -e
BINARY="./SimpleView.app/Contents/MacOS/SimpleView"
FRAMEW_FOLDER="SimpleView.app/Contents/Frameworks/"
LIBSNDFILE_DIR="/usr/local/lib"

if [ -d "$FRAMEW_FOLDER" ]
then
    echo ${FRAMEW_FOLDER} exists
else
    mkdir ${FRAMEW_FOLDER}
fi
function DoInstallNameTool {
xLIB="$1"
xLIB_NAME="$2"
xBINARY="$3"
echo install_name_tool -change \"${xLIB}\" \"@executable_path/../Frameworks/${xLIB_NAME}\" \"${xBINARY}\"
install_name_tool -id "@executable_path/../Frameworks/${xLIB_NAME}" "${FRAMEW_FOLDER}${xLIB_NAME}"
install_name_tool -change ${xLIB} "@executable_path/../Frameworks/${xLIB_NAME}" "${xBINARY}"
}

        for LIBout in $(otool -L "${BINARY}"| tail -n +2 | grep libvtk| grep -v executable | cut -d '(' -f -1)
        do
                echo "Handling Lib: $LIBout"
                #LIB_NAME=$(basename "$LIBout")
                LIB_NAME=$(basename "$LIBout" | rev | cut -d '/' -f 1 | rev)
                #echo "    Adding ${LIB_NAME}"
                LIBnew=$(echo "${LIBSNDFILE_DIR}/${LIB_NAME}")
                cp -Rf "${LIBnew}" "${FRAMEW_FOLDER}"

                DoInstallNameTool "$LIBout" "$LIB_NAME" "$BINARY"

                LIBnew=$(echo "${FRAMEW_FOLDER}${LIB_NAME}")
                echo "${LIBnew}"

                #DoInstallNameTool "$LIBnew" "$LIB_NAME" "$LIBnew"

            for LIB in $(otool -L "${LIBnew}" | tail -n +2 | grep libvtk| grep -v executable | cut -d '(' -f -1)
            do
                #echo "Handling Lib: $LIB"
                LIB_NAME=$(basename "$LIB" | rev | cut -d '/' -f 1 | rev )
                #echo "    Adding ${LIB_NAME}"
                cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME}" "${FRAMEW_FOLDER}"

                DoInstallNameTool "$LIB" "$LIB_NAME" "$LIBnew"
            done
        done

        echo "Second part---------------------------------------------------------------"
        for LIBnew in $(ls ${FRAMEW_FOLDER}| grep libvtk)
        do
                echo "Handling Lib: $LIBnew"
            for LIB in $(otool -L "${FRAMEW_FOLDER}${LIBnew}" | tail -n +2 | grep libvtk| grep -v executable | cut -d '(' -f -1)
            do
                LIB_NAME=$(basename "$LIB" | rev | cut -d '/' -f 1 | rev )
                #echo "    Adding ${LIB_NAME}"
                #cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME}" "${FRAMEW_FOLDER}"

                DoInstallNameTool "$LIB" "$LIB_NAME" "${FRAMEW_FOLDER}$LIBnew"
            done
        done

LIBSNDFILE_DIR="/Users/cxx/Qt/5.5/clang_64/lib"

  for LIB in $(otool -L "${BINARY}"|grep Qt|grep -v 'vtk' |cut -d '(' -f -1 )
        do
            echo "Handling Lib: $LIB"
            LIB_NAME=$(echo $LIB | rev | cut -d '/' -f 1 | rev)
            echo "    Adding ${LIB_NAME}"
            if [ -d "${FRAMEW_FOLDER}${LIB_NAME}.framework" ] 
            then 
                echo "${FRAMEW_FOLDER}/${LIB_NAME}.framework" exists
            else
                cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME}.framework" "${FRAMEW_FOLDER}"
            fi

            DoInstallNameTool "$LIB" "$LIB_NAME.framework/Versions/5/$LIB_NAME" "$BINARY"
  for LIB in $(otool -L "${FRAMEW_FOLDER}${LIB_NAME}.framework/Versions/5/${LIB_NAME}"|grep rpath|grep -v 'vtk' |cut -d '(' -f -1 )
        do
            #echo "Handling Lib: $LIB"
            LIB_NAME2=$(echo $LIB | rev | cut -d '/' -f 1 | rev)
            #echo "    Adding ${LIB_NAME}"
            if [ -d "${FRAMEW_FOLDER}${LIB_NAME2}.framework" ] 
            then 
                echo "${FRAMEW_FOLDER}/${LIB_NAME2}.framework" exists
            else
                cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME2}.framework" "${FRAMEW_FOLDER}"
            fi

            DoInstallNameTool "$LIB" "$LIB_NAME2.framework/Versions/5/$LIB_NAME2" "${FRAMEW_FOLDER}${LIB_NAME}.framework/Versions/5/${LIB_NAME}"
        done


        done
        LIB_NAME="QtDBus"
            if [ -d "${FRAMEW_FOLDER}${LIB_NAME}.framework" ] 
            then 
                echo "${FRAMEW_FOLDER}/${LIB_NAME}.framework" exists
            else
                cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME}.framework" "${FRAMEW_FOLDER}"
            fi

            DoInstallNameTool "$LIB" "$LIB_NAME.framework/Versions/5/$LIB_NAME" "${FRAMEW_FOLDER}${LIB_NAME}.framework/Versions/5/${LIB_NAME}"
     for LIB in $(otool -L "${FRAMEW_FOLDER}${LIB_NAME}.framework/Versions/5/${LIB_NAME}"|grep rpath|grep -v 'vtk' |cut -d '(' -f -1 )
        do
            #echo "Handling Lib: $LIB"
            LIB_NAME2=$(echo $LIB | rev | cut -d '/' -f 1 | rev)
            #echo "    Adding ${LIB_NAME}"
            if [ -d "${FRAMEW_FOLDER}${LIB_NAME2}.framework" ] 
            then 
                echo "${FRAMEW_FOLDER}/${LIB_NAME2}.framework" exists
            else
                cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME2}.framework" "${FRAMEW_FOLDER}"
            fi

            DoInstallNameTool "$LIB" "$LIB_NAME2.framework/Versions/5/$LIB_NAME2" "${FRAMEW_FOLDER}${LIB_NAME}.framework/Versions/5/${LIB_NAME}"
        done



#   for LIBnew in $(ls ${FRAMEW_FOLDER}| grep vtkViewsQt)
#        do
#                echo "Handling Lib: $LIBnew"
#            for LIB in $(otool -L "${FRAMEW_FOLDER}${LIBnew}" | tail -n +2 | grep Qt | grep -v 'vtk'|cut -d '(' -f -1)
#            do
#                LIB_NAME=$(basename "$LIB" | rev | cut -d '/' -f 1 | rev )
#                #echo "    Adding ${LIB_NAME}"
#                #cp -Rf "${LIBSNDFILE_DIR}/${LIB_NAME}" "${FRAMEW_FOLDER}"
#
#                DoInstallNameTool "$LIB" "$LIB_NAME.framework/Versions/5/${LIB_NAME}" "${FRAMEW_FOLDER}$LIBnew"
#            done
#        done
#


