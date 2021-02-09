#!/bin/bash
# Standard simple shell script to quickly commit all changes

echo "Enter your commit to this push: "
read  COMMIT

git init
git add --all
git commit --all -m $COMMIT
git push
