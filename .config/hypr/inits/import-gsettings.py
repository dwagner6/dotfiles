#!/usr/bin/python3
# usage: import-gsettings
import configparser
import os
import os.path

from gi import require_version
require_version('Gio', '2.0')
from gi.repository import Gio

translate_keys = {
        'gtk-theme-name': 'gtk-theme',
        'gtk-icon-theme-name': 'icon-theme',
        'gtk-cursor-theme-name': 'cursor-theme',
        'gtk-font-name': 'document-font-name',
        }

config = configparser.ConfigParser()
config.read([
    os.path.expandvars('$XDG_CONFIG_HOME/gtk-3.0/settings.ini'),
    os.path.expanduser('~/.config/gtk-3.0/settings.ini')])

sect = config['Settings']

iface = Gio.Settings.new('org.gnome.desktop.interface')

for key in translate_keys:
    if sect[key]:
        iface.set_string(translate_keys[key], sect[key])
