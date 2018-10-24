#!/bin/bash
# test redirect

for file in `ls`; do
    #statements
    echo `wc -l ${file}`
done

# sed command test
# sed -e "1a\addanewLine testfile"
# replace content and redirect to new file
sed 's/hello/test/' testfile | nl  > newfile

# replace content to original file
sed -i 's/appl/abc/g' testfile
sed -i 's:a:A:g' testfile

# remove blank space
sed -i '/^$/d' testfile

