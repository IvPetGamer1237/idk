#!/usr/bin/bash
read -ep "fakeshell user: " user
read -ep "fakeshell hostname: " host

while true
do
    if [[ $(pwd) == $HOME ]]
    then
        dir="~"
    else
	    dir=$(basename $(pwd))
    fi
	read -ep "[$user@$host $dir]\$ " command
	if $command 
    then
        continue
    else
        echo "fakeshell: $command: command not found"
    fi
done
