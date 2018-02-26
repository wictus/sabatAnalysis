./sabatanalysis $1 ../data/baseSpectra/total/dataStudentUkraine/C/1E8_LaBr3_3x3_FWHM_C_out.txt_sorted.txt ../data/baseSpectra/total/dataStudentUkraine/S/1E8_LaBr3_3x3_FWHM_S_out.txt_sorted.txt ../data/baseSpectra/total/dataStudentUkraine/Cl/1E8_LaBr3_3x3_FWHM_Cl_out.txt_sorted.txt ../data/baseSpectra/total/dataStudentUkraine/O/1E8_LaBr3_3x3_FWHM_O_out.txt_sorted.txt ../data/baseSpectra/total/dataStudentUkraine/H/1E8_LaBr3_3x3_FWHM_H_out.txt_sorted.txt 
 
outName=${0:2}
outName=${outName%%.*}
mv fit.png $outName'_fit.png'
mv coctail.png $outName'_coctail.png' 
mv difference.png $outName'_difference.png' 
