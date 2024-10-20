#!/bin/bash

# Block middle click paste
# xmousepasteblock &

# Delayed startups
sleep 10

#flatpak run com.discordapp.Discord &

exec-once = [workspace 1 silent] kitty --detach tmux
exec-once = [workspace 2 silent] firefox
exec-once = [workspace 3 silent] vesktop

pypr &

onedrive-mount &
