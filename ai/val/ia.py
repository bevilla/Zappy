import sys
from incantation import incantation
from ia_socket import IA_Socket

max_item = {
    'nourriture': 15,
    'linemate': 9,
    'deraumere' : 8,
    'sibur' : 10,
    'mendiane' : 5,
    'phiras' : 6,
    'thystame' : 1
}

class           IA:

    # Prologue

    def __init__(self, host, port, name, verbose=False):
        self.name = name
        self.verbose = verbose
        self.level = 1

        self.server = IA_Socket(host=host, port=port, verbose=self.verbose)
        self.server.connect()
        self.bienvenue()
        self.sendTeam()
        self.width, self.height = self.getMapSize()

    def bienvenue(self):
        if self.server.sread() != 'BIENVENUE':
            raise Exception("The specified server isn't a zappy_server")

    def sendTeam(self):
        self.server.send(self.name)
        resp = self.server.sread()
        if resp == 'ko':
            raise Exception("Specified team name isn't a valid one")
        elif resp.isdigit():
            return int(resp)
        return -1

    def getMapSize(self):
        msg = self.server.sread()
        msg = msg.split(' ')
        if len(msg) != 2:
            raise Exception("The specified server isn't a zappy_server")
        return int(msg[0]), int(msg[1])

    # Fin Prologue

    def run(self):
        while 1:
            read, write, opt = self.server.select()
            if self.server.getSock() in read:
                buf = self.server.read()
                if buf == 'mort':
                    sys.exit(0)
                else:
                    print 'lol -> ' + buf
            self.lookForItems()
            self.tryIncantation()

    # Incantation

    def canIncantationOnCell(self, inc):
        if inc.has_key('player') and inc['player'] -1 > 0:
            return False
        inv = self.inventaire()
        for k, v in inc.iteritems():
            if k != 'player' and inv[k] < inc[k]:
                cell = self.voir()[0]
                if cell.has_key(k) and cell[k] + inv[k] >= inc[k]:
                    return False
        return True

    def cleanCell(self, inc):
        cell = self.voir()[0]
        cell.pop('nourriture', 0)
        cell.pop('joueur', 0)
        for k, v in cell.iteritems():
            if not inc.has_key(k):
                while cell.has_key(k) and cell[k] > 0:
                    self.prend(k)
                    cell = self.voir()[0]
                    cell.pop('nourriture', 0)
                    cell.pop('joueur', 0)
            elif cell[k] > inc[k]:
                while cell.has_key(k) and cell[k] > inc[k]:
                    self.prend(k)
                    cell = self.voir()[0]
                    cell.pop('nourriture', 0)
                    cell.pop('joueur', 0)

    def setIncantation(self, inc):
        cell = self.voir()[0]
        cell.pop('nourriture', 0)
        cell.pop('joueur', 0)
        for k, v in inc.iteritems():
            while k != 'player' and cell.get(k, 0) < inc[k] and self.inventaire()[k] > 0:
                self.pose(k)
                cell = self.voir()[0]
                cell.pop('nourriture', 0)
                cell.pop('joueur', 0)
            cell = self.voir()[0]
            cell.pop('nourriture', 0)
            cell.pop('joueur', 0)

    def tryIncantation(self):
        inc = dict(incantation[self.level])
        if self.canIncantationOnCell(inc):
            self.cleanCell(inc)
            self.setIncantation(inc)
            res = self.incantation()
            if res > 0:
                self.level = res
                return True
        return False

    # Fin Incantation

    def lookForItems(self):
        cell = self.voir()[0]
        inv = self.inventaire()
        for k, v in cell.iteritems():
            if inv.has_key(k) and inv[k] < max_item[k]:
                self.prend(k)

    # Utils

    def cleanAndSplit(self, msg):
        msg = msg.replace('{', '')
        msg = msg.replace('}', '')
        return msg.split(',')

    # Inventaire

    def getInventory(self, msg):
        inv = dict()
        for elem in msg:
            elem = elem.strip()
            elem = elem.split(' ')
            if len(elem) != 2 or not elem[1].isdigit():
                raise Exception("The specified server isn't a zappy_server")
            inv[elem[0]] = int(elem[1])
        return inv

    def inventaire(self):
        self.server.send('inventaire')
        resp = self.server.sread(timeout=None)
        resp = self.cleanAndSplit(resp)
        return self.getInventory(resp)

    # Voir

    def checkVoirFormat(self, msg):
        n = len(msg)
        i = 4
        old = 3
        while i < n:
            old += 2
            i += old
        if i != n:
            print '==========='
            print msg
            print '==========='
            raise Exception("The specified server isn't a zappy_server")

    def getVoirCell(self, msg):
        cell = dict()
        msg = msg.strip()
        msg = msg.split(' ')
        for elem in msg:
            if cell.has_key(elem):
                cell[elem] += 1
            else:
                cell[elem] = 1
        return cell

    def getVision(self, msg):
        i = 0
        vision = dict()
        while i < len(msg):
            vision[i] = self.getVoirCell(msg[i])
            i += 1
        return vision

    def voir(self):
        self.server.send('voir')
        resp = self.server.sread(timeout=None)
        resp = self.cleanAndSplit(resp)
        self.checkVoirFormat(resp)
        return self.getVision(resp)

    # Fin Voir

    def incantation(self):
        self.server.send('incantation')
        resp = self.server.sread(timeout=None)
        if resp == 'ko':
            return False
        elif resp != 'elevation en cours':
            raise Exception("The specified server isn't a zappy_server")
        resp = self.server.sread(timeout=None)
        if resp == 'ko':
            return False
        elif not resp.startswith('niveau actuel : '):
            raise Exception("The specified server isn't a zappy_server")
        resp = resp.split(' ')
        if not resp[-1].isdigit():
            raise Exception("The specified server isn't a zappy_server")
        return int(resp[-1])

    def avance(self):
        self.server.send('avance')
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def droite(self):
        self.server.send('droite')
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def gauche(self):
        self.server.send('gauche')
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def prend(self, item):
        msg = 'prend ' + item
        self.server.send(msg)
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def pose(self, item):
        msg = 'pose ' + item
        self.server.send(msg)
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def expulse(self):
        self.server.send('expulse')
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def broadcast(self, msg):
        msg = 'broadcast ' + msg
        self.server.send(msg)
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def fork(self):
        self.server.send('fork')
        resp = self.server.sread(timeout=None)
        if resp == 'ok':
            return True
        return False

    def connect_nbr(self):
        self.server.send('connect_nbr')
        resp = self.server.sread(timeout=None)
        if resp.isdigit():
            return int(resp)
        return -1
