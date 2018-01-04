#!/usr/bin/python

import os
import socket
import select
from utils import my_print

class           Server:

    def __init__(self, host, port):
        from bonus import quit_client

        self.host = host
        self.port = int(port)
        self.address = (self.host, self.port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(self.address)
        self.sockfd = self.sock.fileno()

    def read(self):
        read, write, opt = select.select([ self.sock ], [ ], [ ], 5)

        if not len(read):
            my_print('Error: Cannot communicate with the server')

        buf = os.read(self.sockfd, 4096)
        if len(buf) == 0:
            my_print('Error: Disconnected from server')
            self.close()
            quit_client()

        print 'server>',
        for line in buf.splitlines():
            my_print(line)

    def write(self, msg):
        read, write, opt = select.select([ ], [ self.sock ], [ ], 5)
        if not len(write):
            my_print('Error: Cannot communicate with the server')
            self.socket.close()
            quit_client()
        os.write(self.sockfd, str(msg) + '\n')

    def close(self):
        self.sock.close()
