#!/usr/bin/python

from __future__ import print_function

import socket
import select
import tty
import sys
import termios
import os

from server import Server
from utils import *
from direction import *
from comm import *

stdin = sys.stdin.fileno()
old_settings = termios.tcgetattr(stdin)

def     quit_client(server):
    server.close()
    sys.exit(0)

def     broadcast(server):
    msg = 'broadcast '
    print(msg, end='')
    c = getch()
    msg += c
    while c != '\r':
        print(c, end='')
        msg += c
        c = getch()
    print('\r')
    server.write(msg)

def     main():
    args = parse()

    ip = args.ip.split('.')
    if len(ip) != 4:
        print('the specified --ip is not an IP address')
        sys.exit(0)
    for elem in ip:
        if not elem.isdigit():
            print('the specified --ip is not an IP address')
            sys.exit(0)

    launch_graphic(args)
    server = Server(host=args.ip, port=args.port)

    tab = dict()

    tab['q'] = 'gauche';
    tab['z'] = 'avance';
    tab['d'] = 'droite';

    tab['h'] = 'voir';
    tab['u'] = 'inventaire';
    tab['i'] = 'expulse';
    tab['p'] = 'incantation';
    tab['m'] = 'fork';
    tab['y'] = 'connect_nbr';

    tab['j'] = 'prend nourriture';
    tab['k'] = 'prend linemate';
    tab['l'] = 'prend deraumere';
    tab['n'] = 'prend sibur';
    tab[','] = 'prend mendiane';
    tab[';'] = 'prend phiras';
    tab[':'] = 'prend thystame';

    tab['J'] = 'pose nourriture';
    tab['K'] = 'pose linemate';
    tab['L'] = 'pose deraumere';
    tab['N'] = 'pose sibur';
    tab['?'] = 'pose mendiane';
    tab['.'] = 'pose phiras';
    tab['/'] = 'pose thystame';

    usage = '\n'
    usage += '     [q]: gauche     [z]: avance       [d]: droite\r\n';
    usage += '     [h]: voir       [u]: inventaire   [i]: expulse\r\n';
    usage += '     [o]: broadcast  [p]: incantation  [m]: fork\r\n';
    usage += '                     [y]: connect_nbr\r\n\n';
    usage += '\t+-------------+------------+------------+\r\n';
    usage += '\t|    item     |    prend   |    pose    |\r\n';
    usage += '\t+-------------+------------+------------+\r\n';
    usage += '\t| nourriture  |      j     |      J     |\r\n';
    usage += '\t| linemate    |      k     |      K     |\r\n';
    usage += '\t| deraumere   |      l     |      L     |\r\n';
    usage += '\t| sibur       |      n     |      N     |\r\n';
    usage += '\t| mendiane    |      ,     |      ?     |\r\n';
    usage += '\t| phiras      |      ;     |      .     |\r\n';
    usage += '\t| thystame    |      :     |      /     |\r\n';
    usage += '\t+-------------+------------+------------+\r\n';

    os.system('clear')

    server.read()
    server.write(args.name)

    os.system('stty -echo')
    tty.setraw(stdin)

    while 1:
        read, write, opt = select.select([ stdin, server.sock ], [ server.sock ], [ ], 0)
        if stdin in read:
            c = getch()
            if c == 'o':
                broadcast(server)
            if c == '0':
                quit_client(server)
            if c == ' ':
                my_print(usage)
            elif tab.has_key(c):
                my_print(tab[c])
                server.write(tab[c])
        if server.sock in read:
            server.read()

if __name__ == "__main__":
    try:
        os.system('stty -echo')
        main()
    finally:
        my_print('-----quit-----')
        os.system('stty echo')
        termios.tcsetattr(stdin, termios.TCSADRAIN, old_settings)
        sys.exit(0)
