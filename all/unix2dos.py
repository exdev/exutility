# ======================================================================================
# File         : unix2dos.py
# Author       : Wu Jie 
# Last Change  : 01/08/2010 | 19:02:18 PM | Friday,January
# Description  : 
# ======================================================================================

#/////////////////////////////////////////////////////////////////////////////
# Replace LF with CRLF in argument files.  Print names of changed files.
#/////////////////////////////////////////////////////////////////////////////

import sys, re, os

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

def main():
    target = "."
    if len(sys.argv) > 1:
        target = sys.argv[1]

    if os.path.isfile(target):
        do_refresh(target)
    else:
        # walk through the path
        for root, dirs, files in os.walk( target, topdown=True ):
            # don't visit .git directories
            if '.git' in dirs:
                dirs.remove('.git') 

            # write files
            for name in files:
                full_filename = os.path.join( root, name ) 
                do_refresh(full_filename)

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

def do_refresh( _filename ):
    if os.path.isdir(_filename):
        print _filename, "Directory!"
        continue
    data = open(_filename, "rb").read()
    if '\0' in data:
        print _filename, "Binary!"
        continue
    newdata = re.sub("\r?\n", "\r\n", data)
    if newdata != data:
        try:
            f = open(_filename, "wb")
        except IOError:
            print _filename, "error to write!"
            return

        f.write(newdata)
        f.close()
        print _filename, "wrote!"

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

if __name__ == '__main__':
    main()
