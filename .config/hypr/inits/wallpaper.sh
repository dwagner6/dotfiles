#!/bin/bash

export PATH="${PATH}:${HOME}/.local/bin/"

swww-daemon --format xrgb

if [ -e "${HOME}/.cache/wal/colors" ]; then
	wal -R

	echo "Cached colors exist. Using existing colors."
else
	DIR=$HOME/wallpapers
	PICS=($(ls ${DIR}))

	RANDOMPICS=${PICS[$RANDOM % ${#PICS[@]}]}

	swww img ${DIR}/${RANDOMPICS} --transition-type wipe --transition-fps 60 --transition-duration 2 --transition-angle 30 --transition-step 90

	wait

	wal -i ${DIR}/${RANDOMPICS}
	wait
	killall swaync
	wait
	swaync

	echo "Successfully set a new wallpaper and generated colors from it."
fi
