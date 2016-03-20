#!/bin/bash
app="SimpleView"
lib=("libvtkViewsQt" "libvtkIOLegacy" "libvtkGUISupportQt" "libvtkRenderingOpenGL" "libvtkViewsInfovis" "libvtkChartsCore" "libvtkFiltersImaging"
	"libvtkInfovisLayout"
	"libvtkInfovisCore"
	"libvtkRenderingContext2D"
	"libvtkRenderingLabel"
	"libvtkViewsCore"
	"libvtkInteractionWidgets"
	"libvtkInteractionStyle"
	"libvtkRenderingVolume"
	"libvtkFiltersModeling"
	"libvtkImagingGeneral"
	"libvtkImagingHybrid"
	"libvtkIOImage"
	"libvtkFiltersHybrid"
	"libvtkImagingSources"
	"libvtkRenderingAnnotation"
	"libvtkRenderingFreeType"
	"libvtkRenderingCore"
	"libvtkCommonColor"
	"libvtkFiltersSources"
	"libvtkFiltersExtraction"
	"libvtkFiltersStatistics"
	"libvtkImagingFourier"
	"libvtkalglib"
	"libvtkFiltersGeneral"
	"libvtkCommonComputationalGeometry"
	"libvtkfreetype"
	"libvtkImagingColor"
	"libvtkImagingCore"
	"libvtkFiltersCore"
	"libvtkIOCore"
	"libvtkCommonExecutionModel"
	"libvtkCommonDataModel"
	"libvtkCommonMisc"
	"libvtkCommonSystem"
	"libvtkCommonTransforms"
	"libvtkCommonMath"
	"libvtkCommonCore"
	"libvtkzlib"
	"libvtksys"
)



install_name_tool -add_rpath /Users/cxx/Qt/5.5/clang_64/lib/ ${app}.app/Contents/MacOS/${app}
name="libvtkRenderVolumeOpenGL"
install_name_tool -change ${name}-7.0.1.dylib /usr/local/vtk7-share/lib/libvtkRenderingVolumeOpenGL-7.0.1.dylib ${app}.app/Contents/MacOS/${app}
for name in ${lib[@]}; do
	echo ${name} 
	install_name_tool -change ${name}-7.0.1.dylib /usr/local/vtk7-share/lib/${name}-7.0.1.dylib ${app}.app/Contents/MacOS/${app}
	install_name_tool -id /usr/local/vtk7-share/lib/${name}-7.0.1.dylib ${app}.app/Contents/MacOS/${app}
done