#!/usr/bin/bash
read -rep "fakeshell user: " user
read -rep "fakeshell hostname: " host

while true
do
    if [[ $(pwd) == "$HOME" ]]
    then
        dir="~"
    else
	    dir=$(basename "$(pwd)")
    fi
	read -rep "[$user@$host $dir]\$ " command
	if $command 
    then
        continue
    else
        echo "fakeshell: $command: command not found"
    fi
done
