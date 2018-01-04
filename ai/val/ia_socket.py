import  os
import  sys
import  socket
import  select

class           IA_Socket:
    def __init__(self, host, port, verbose=False):
        self.host = host
        self.port = port
        self.addr = (self.host, self.port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.fd = self.sock.fileno()
        self.verbose = verbose

    def connect(self):
        self.sock.connect(self.addr)

    def select(self):
        return select.select([ self.sock ], [ self.sock ], [ ], 5)

    def rselect(self, timeout=5):
        if not timeout:
            return select.select([ self.sock ], [ ], [ ])
        return select.select([ self.sock ], [ ], [ ], 5)

    def wselect(self):
        return select.select([ ], [ self.sock ], [ ], 5)

    def read(self):
        buf = self.sock.recv(4096 << 1)
        buf = buf.strip()
        if self.verbose:
            print 'server>',
            print buf
        if buf == 'mort':
            sys.exit(0)
        return buf

    def sread(self, timeout=5):
        read, write, opt, = self.rselect(timeout)
        if self.sock in read:
            buf = self.sock.recv(4096 << 1)
            buf = buf.strip()
            if self.verbose:
                print 'server>',
                print buf
            if buf == 'mort':
                sys.exit(0)
            return buf
        return ''

    def send(self, msg):
        read, write, opt, = select.select([ ], [ self.sock ], [ ], 5)
        if self.verbose:
            print msg
        if self.sock in write:
            msg += '\n'
            self.sock.sendall(msg)
            return True
        return False

    def close(self):
        self.sock.close()

    def getSock(self):
        return self.sock
