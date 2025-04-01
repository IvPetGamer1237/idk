#!/usr/bin/bash
echo -n "fakeshell user:"
read -er user
echo -n "fakeshell hostname:"
read -er host
clear
for (( ; ; ))
do
	dir=$(pwd) 
	echo -n "[$user@$host $dir]\$ "
	read -er command
	$command
done
