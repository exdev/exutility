# ======================================================================================
# File         : refresh_files.py
# Author       : Wu Jie 
# Last Change  : 01/08/2010 | 18:20:03 PM | Friday,January
# Description  : 
# ======================================================================================

#/////////////////////////////////////////////////////////////////////////////
# refresh file by write it again with nothing changes
#/////////////////////////////////////////////////////////////////////////////

import sys, os

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
        print _filename, "directory!"
        return

    data = open(_filename, "rb").read()
    if '\0' in data:
        print _filename, "binary!"
        return

    try:
        f = open(_filename, "wb")
    except IOError:
        print _filename, "error to write!"
        return

    f.write(data)
    f.close()
    print _filename, "wrote!"

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

if __name__ == '__main__':
    main()
