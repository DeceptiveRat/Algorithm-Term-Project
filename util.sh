#!/bin/sh 

if [ $# -eq 0 ]; then
	echo "usage: util.sh <command>"
	exit 1
fi

command="$1"

if [ "$command" = "clearOutcome" ]; then
	echo "removing all outcome files"
	rm outcome*
fi
