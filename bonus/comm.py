#!/usr/bin/python

import socket
import select
import sys
import os

def     read_server(server):
    read, write, opt = select.select([ server ], [ ], [ ], 5)
    if not len(read):
        my_print('Error: Cannot communicate with the server')
        sys.exit(1)
    buf = os.read(server.fileno(), 4096)
    if len(buf) == 0:
        my_print('Error: Disconnected from server')
        quit_client()
    print 'server> ',
    for line in buf.splitlines():
        my_print(line)
