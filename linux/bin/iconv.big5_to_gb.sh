# ======================================================================================
# File         : iconv.big5_to_gb.sh
# Author       : Wu Jie 
# Last Change  : 10/18/2010 | 13:51:14 PM | Monday,October
# Description  : 
# ======================================================================================

for file in *.srt ; do
    echo Converting "$file"... 
    iconv -c -f BIG5 -t GB18030 "$file" > "$file.cov"
done
