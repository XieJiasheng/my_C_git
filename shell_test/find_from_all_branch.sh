#!/bin/bash
# to pull all branch from remote depository

all_branch=`git branch | grep -v '*'`
current_branch=`git branch | grep "* " | awk '{print $2}'`
echo "current branch is "${current_branch}
git pull --all
for branch in ${all_branch[*]}; do
    #statements
    git checkout ${branch}
    if [[ $# -gt 0 ]]; then
        $1
    fi
    # git pull --all
    # echo "${branch} update success"
done
git checkout ${current_branch}
# echo ${all_branch}

# if [[ $# -gt 0 ]]; then
#     #statements
#     $1
#     echo "data"
# fi
# echo "this"