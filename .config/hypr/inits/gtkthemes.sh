#!/bin/bash

# Fix running gtk apps on root
exec-once = xhost +SI:localuser:root

## Set GTK Themes, Icons, Cursor and Fonts
THEME='Breeze-Dark'
ICONS='Papirus-Dark'
FONT='SF Pro Display Regular 11'
CURSOR='Adwaita'

SCHEMA='gsettings set org.gnome.desktop.interface'

apply_themes() {
	${SCHEMA} gtk-theme "$THEME"
	${SCHEMA} icon-theme "$ICONS"
	${SCHEMA} cursor-theme "$CURSOR"
	${SCHEMA} font-name "$FONT"
}

apply_themes
