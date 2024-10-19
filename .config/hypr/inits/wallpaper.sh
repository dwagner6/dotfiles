#!/bin/bash

export PATH="${PATH}:${HOME}/.local/bin/"

swww-daemon --format xrgb

DIR=$HOME/wallpapers
PICS=($(ls ${DIR}))

RANDOMPICS=${PICS[$RANDOM % ${#PICS[@]}]}

swww img ${DIR}/${RANDOMPICS} --transition-type wipe --transition-fps 60 --transition-duration 2 --transition-angle 30 --transition-step 90

wait

echo "Successfully set a new wallpaper."
