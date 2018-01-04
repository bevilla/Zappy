#!/usr/bin/python

import os
import argparse
import sys
import tty
import termios

graph_bin = './zappy-gfx-linux64'

def     parse():
    parser = argparse.ArgumentParser(description='A simple interface for the {EPITECH.} Zappy project.')
    parser.add_argument('-i', '--ip', default='127.0.0.1', help="The server's ip")
    parser.add_argument('-p', '--port', default='4242', help="The server's port")
    parser.add_argument('-g', '--graphic', default=False, action='store_true', help="Launch the graphical interface")
    parser.add_argument('-v', '--verbose', default=False, action='store_true', help="The team you want to be on")
    parser.add_argument('-n', '--name', required=True, help="The team you want to be on")
    return parser.parse_args()

def     getch():
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

def     launch_graphic(args):
    if args.graphic:
        cmd = graph_bin + ' ' + args.ip + ' ' + args.port
        if not args.verbose:
            cmd += ' >/dev/null'
        cmd += ' &'
        print cmd
        os.system(cmd)

def     my_print(msg):
    print(str(msg) + '\r')
