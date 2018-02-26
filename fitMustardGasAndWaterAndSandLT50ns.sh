./sabatanalysis $1 ../data/baseSpectra/timeGateLs50ns/Prompt\ -\ submarine\ 10\ cm/C/7.9_1E8_LaBr3_3x3_FWHM_C_out_t_lt_50ns__sorted_cell__13_CUT.txt ../data/baseSpectra/timeGateLs50ns/Prompt\ -\ submarine\ 10\ cm/S/7.9_1E8_LaBr3_3x3_FWHM_S_t_lt_50ns_out__sorted_cell__13_CUT.txt ../data/baseSpectra/timeGateLs50ns/Prompt\ -\ submarine\ 10\ cm/Cl/joinedClorines.txt ../data/baseSpectra/timeGateLs50ns/Prompt\ -\ submarine\ 10\ cm/O/7.9_1E8_LaBr3_3x3_FWHM_O_t_lt_50ns_out__sorted_cell__13_CUT.txt ../data/baseSpectra/timeGateLs50ns/Prompt\ -\ submarine\ 10\ cm/H/7.9_1E8_LaBr3_3x3_FWHM_H_t_lt_50ns_out__sorted_cell__13_CUT.txt ../data/baseSpectra/timeGateLs50ns/Prompt\ -\ submarine\ 10\ cm/Si/7.9_1E8_LaBr3_3x3_FWHM_Si_t_lt_50ns_out__sorted_cell__13_CUT.txt
 
outName=${0:2}
outName=${outName%%.*}
mv fit.png $outName'_fit.png'
mv coctail.png $outName'_coctail.png' 
mv difference.png $outName'_difference.png' 
