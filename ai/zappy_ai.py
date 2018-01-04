#!/usr/bin/python2.7

import socket
import sys
import string
import re
import time
from random import randint

RED = '\033[01;31m'
BLUE = '\033[01;34m'
PINK = '\033[01;35m'
CYAN = '\033[01;36m'
STOP = '\033[0m'
DEFAULT_HOST = '127.0.0.1'
DEFAULT_PORT = 4242
DEFAULT_IA = "hard"
READ_SIZE = 100000

def usage():
    print CYAN, "Usage: ./client.py [OPTIONS]"
    print "\t-n teamname"
    print "\t-p port"
    print "\t-h hostname"
    print "\t-d difficulty of AI [random | easy | medium | hard]", STOP

def parse(ac, av):
    if ac < 3:
        raise ValueError('Error : Need at least 2 arguments : "-n" and "teamname"')
    i = 1
    host = None
    port = None
    team = None
    ia = None
    while i < ac:
        if av[i] in "-n":
            team = av[i + 1]
        elif av[i] in "-p":
            try:
                port = int(av[i + 1])
            except:
                raise ValueError('Error : "-p" must be followed by a number')
        elif av[i] in "-h":
            host = av[i + 1]
        elif av[i] in "-d":
            ia = av[i + 1]
        else:
            raise ValueError('Error : ' + av[i] + " is a wrong entry")
        i += 2
    if team is None:
        raise ValueError('Error : missing -n')
    if host is None:
        host = DEFAULT_HOST
    if port is None:
        port = DEFAULT_PORT
    if ia is None:
        ia = DEFAULT_IA
    return team, host, port, ia

def parse_voir_inv(cmd):
    info = list()
    i = 0
    while i < (len(cmd) - 2):
        line = ""
        while i < (len(cmd) - 2) and cmd[i] != ',' and cmd[i] != '}':
            line += cmd[i]
            i += 1
        if cmd[i] == ',':
            i += 1
        info.append(line)
    return info

def calc_front(i):
    n = 1
    if i == 0:
        return 0
    while pow(n + 1, 2) <= i:
        n += 1
    return n

def calc_side(i, front):
    return i - (pow(front, 2) + front)

def parse_clear(square):
    item = list()
    i = 0
    while i < len(square):
        line = ""
        while i < len(square) and square[i] != ' ':
            line += square[i]
            i += 1
        if i < len(square):
            i += 1
        item.append(line)
    return item

def clean_square(s):
    send_cmd(s, "voir")
    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
    print RED, 'Received message : ', cmd, STOP
    if "{" not in cmd:
        while "{" not in cmd:
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
    list_square = parse_voir_inv(cmd)
    if len(list_square) == 0:
        return 0
    square = string.replace(list_square[0], '{ ', '')
    square = string.replace(square, 'joueur ', '')
    square = string.replace(square, 'joueur,', '')
    to_clear_list = parse_clear(square)
    for i in range(len(to_clear_list)):
        send_and_recv(s, "prend " + to_clear_list[i])

def voir_analyse(cmd, item):
    print RED, 'Received message : ', cmd, STOP
    if cmd[0] != '{':
        return None, None
    voir_list = parse_voir_inv(cmd)
    for i in range(len(voir_list)):
        if item in voir_list[i]:
            front = calc_front(i)
            side = calc_side(i, front)
            return front, side
    return None, None

def voir_happy_analyse(cmd, item):
    print RED, 'Received message : ', cmd, STOP
    if cmd[0] != '{':
        return None, None
    voir_list = parse_voir_inv(cmd)
    for i in range(len(voir_list)):
        if item in voir_list[i] and 'joueur' not in voir_list[i]:
            front = calc_front(i)
            side = calc_side(i, front)
            return front, side
    return None, None

def handle_broadcast(s, cmd):
    if '1,' in cmd or '2,' in cmd:
        send_and_recv(s, "avance")
    if '3,' in cmd or '4,' in cmd:
        send_and_recv(s, "gauche")
        send_and_recv(s, "avance")
    if '5,' in cmd or '6,' in cmd:
        send_and_recv(s, "gauche")
        send_and_recv(s, "gauche")
        send_and_recv(s, "avance")
    if '7,' in cmd or '8,' in cmd:
        send_and_recv(s, "droite")
        send_and_recv(s, "avance")

def send_cmd(s, cmd):
    s.send(cmd + '\n')
    print BLUE, 'Sending message : ', cmd, STOP

def recv_msg(s):
    data = string.replace(s.recv(READ_SIZE), '\n', '')
    if "mort" in data:
        sys.exit(PINK + "Vous etes mort" + STOP)
    elif "message" in data:
        while "message" in data:
            print RED, 'Received message : ', data, STOP
            data = string.replace(s.recv(READ_SIZE), '\n', '')
    print RED, 'Received message : ', data, STOP

def send_and_recv(s, cmd):
    send_cmd(s, cmd)
    data = string.replace(s.recv(READ_SIZE), '\n', '')
    while "ok" not in data and "ko" not in data:
        if "mort" in data:
            sys.exit(PINK + "Vous etes mort" + STOP)
        data = string.replace(s.recv(READ_SIZE), '\n', '')
    print RED, 'Received message : ', data, STOP

def init_cmd(s, team):
    recv_msg(s)
    send_cmd(s, team)
    p_id = string.replace(s.recv(READ_SIZE), '\n', '')
    if "ko" in p_id:
        sys.exit(PINK + "Can't connect to the server : team full or invalid" + STOP)
    print RED, 'Received message : ', p_id, STOP
    data = string.replace(s.recv(READ_SIZE), '\n', '')
    print RED, 'Received message : ', data, STOP
    ret = ""
    i = 0
    while data[i] != ' ':
        ret += data[i]
        i += 1
    return int(p_id), int(ret)

def seek(s, item):
    send_cmd(s, "voir")
    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
    if "message" in cmd:
        while "{" not in cmd:
            print RED, 'Received message : ', cmd, STOP
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
        print RED, 'Received message : ', cmd, STOP
    elif "mort" in cmd:
        sys.exit(PINK + "Vous etes mort" + STOP)
    x, y = voir_happy_analyse(cmd, item)
    if x is None and y is None:
        send_and_recv(s, "avance")
    else:
        for i in range(x):
            send_and_recv(s, "avance")
        if y > 0:
            send_and_recv(s, "droite")
        elif y < 0:
            y *= -1
            send_and_recv(s, "gauche")
        for i in range(y):
            send_and_recv(s, "avance")
        send_cmd(s, "prend " + item)
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        while 42:
            if "ok" in data:
                return 1
            elif "ko" in data:
                return 0
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
    return 0

def roam(s, roam_info):
    global map_size
    if roam_info < map_size:
        send_and_recv(s, "avance")
        return (roam_info + 1)
    else:
        send_and_recv(s, "droite")
        send_and_recv(s, "avance")
        send_and_recv(s, "avance")
        send_and_recv(s, "avance")
        send_and_recv(s, "gauche")
        return (0)

def try_to_kill_all(s, roam_info):
    send_cmd(s, "voir")
    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
    if "message" in cmd:
        while "{" not in cmd:
            print RED, 'Received message : ', cmd, STOP
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
        print RED, 'Received message : ', cmd, STOP
    elif "mort" in cmd:
        sys.exit(PINK + "Vous etes mort" + STOP)
    x, y = voir_analyse(cmd, "joueur linemate")
    if x is None and y is None:
        roam_info = roam(s, roam_info)
        return roam_info
    else:
        for i in range(x):
            send_and_recv(s, "avance")
        if y > 0:
            send_and_recv(s, "droite")
        elif y < 0:
            y *= -1
            send_and_recv(s, "gauche")
        for i in range(y):
            send_and_recv(s, "avance")
    send_cmd(s, "voir")
    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
    if "message" in cmd:
        while "{" not in cmd:
            print RED, 'Received message : ', cmd, STOP
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
        print RED, 'Received message : ', cmd, STOP
    elif "mort" in cmd:
        sys.exit(PINK + "Vous etes mort" + STOP)
    x, y = voir_analyse(cmd, "joueur joueur linemate")
    if x is None and y is None:
        roam_info = roam(s, roam_info)
        return roam_info
    else:
        if x == 0 and y == 0:
            send_and_recv(s, "prend linemate")
            print CYAN, "I've fucked up someone's incantation ! <:", STOP
            send_and_recv(s, "broadcast J't'ai baiseyy ! <:")
        return roam_info

def ia_random(team, s):
    while 42:
        rand = randint(0,9)
        if rand is 0:
            send_and_recv(s, "gauche")
            send_and_recv(s, "avance")
        elif rand is 1:
            send_and_recv(s, "droite")
            send_and_recv(s, "avance")
        elif rand is 2:
            send_and_recv(s, "prend nourriture")
        elif rand is 3:
            send_and_recv(s, "prend linemate")
        elif rand is 4:
            send_and_recv(s, "prend deraumere")
        elif rand is 5:
            send_and_recv(s, "prend sibur")
        elif rand is 6:
            send_and_recv(s, "prend mendiane")
        elif rand is 7:
            send_and_recv(s, "prend phiras")
        elif rand is 8:
            send_and_recv(s, "prend thystame")
        else:
            send_and_recv(s, "avance")

def survie(s):
    seek(s, "nourriture")

def level1(team, s):
    send_cmd(s, "voir")
    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
    if "message" in cmd:
        while "{" not in cmd:
            print RED, 'Received message : ', cmd, STOP
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
        print RED, 'Received message : ', cmd, STOP
    elif "mort" in cmd:
        sys.exit(PINK + "Vous etes mort" + STOP)
    x, y = voir_analyse(cmd, "linemate")
    if x is None and y is None:
        send_and_recv(s, "avance")
    else:
        for i in range(x):
            send_and_recv(s, "avance")
        if y > 0:
            send_and_recv(s, "droite")
        elif y < 0:
            y *= -1
            send_and_recv(s, "gauche")
        for i in range(y):
            send_and_recv(s, "avance")
        send_and_recv(s, "prend linemate")
        clean_square(s)
        send_and_recv(s, "pose linemate")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        if "ko" in data:
            print RED, 'Received message : ', data, STOP
        else:
            print RED, 'Received message : ', data, STOP
            data = string.replace(s.recv(READ_SIZE), '\n', '')
            while "niveau" not in data:
                if "mort" in data:
                    sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
                elif "ko" in data:
                    return 1
                data = string.replace(s.recv(READ_SIZE), '\n', '')
            print RED, 'Received message : ', data, STOP
            return 2
    seek(s, "nourriture")
    return 1

def level2(team, s):
    global player_id
    print CYAN, "You're ID is : ", player_id, STOP
    print CYAN, "Waiting...", STOP
    time.sleep(1)
    if (player_id % 2) == 1:
        print CYAN, "I'm a commander !", STOP
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "phiras")
        found = 0
        while found == 0:
            found = seek(s, "phiras")
        send_and_recv(s, "broadcast 2-3 " + team + str(player_id - 1))
        send_cmd(s, "voir")
        cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        if "message" in cmd:
            while "{" not in cmd:
                print RED, 'Received message : ', cmd, STOP
                cmd = string.replace(s.recv(READ_SIZE), '\n', '')
                if "mort" in cmd:
                    sys.exit(PINK + "Vous etes mort" + STOP)
            print RED, 'Received message : ', cmd, STOP
        elif "mort" in cmd:
            sys.exit(PINK + "Vous etes mort" + STOP)
        x, y = voir_analyse(cmd, "joueur joueur")
        while x != 0 and y != 0:
            send_and_recv(s, "broadcast 2-3 " + team + str(player_id - 1))
            send_cmd(s, "voir")
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "message" in cmd:
                while "{" not in cmd:
                    print RED, 'Received message : ', cmd, STOP
                    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
                    if "mort" in cmd:
                        sys.exit(PINK + "Vous etes mort" + STOP)
                print RED, 'Received message : ', cmd, STOP
            elif "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
            x, y = voir_analyse(cmd, "joueur joueur")
        clean_square(s)
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose sibur")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "elevation en cours" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort" + STOP)
            elif "ko" in data:
                return 2
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "niveau" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            elif "ko" in data:
                return 2
            data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose phiras")
        send_and_recv(s, "pose phiras")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "elevation en cours" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort" + STOP)
            elif "ko" in data:
                send_and_recv(s, "incantation")
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "niveau" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            elif "ko" in data:
                s.send("incantation\n")
            data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        return 4
    else:
        print CYAN, "I'm a soldier !", STOP
        cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        lf = str(team) + str(player_id)
        global level
        lf2 = str(level) + "-" + str(level + 1)
        while "niveau actuel : 4" not in cmd:
            if lf in cmd and lf2 in cmd:
                handle_broadcast(s, cmd)
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        return 4

def level4(team, s):
    global player_id
    print CYAN, "You're ID is : ", player_id, STOP
    print CYAN, "Waiting...", STOP
    time.sleep(1)
    if (player_id % 4) == 3:
        print CYAN, "I'm a commander !", STOP
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "phiras")
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "mendiane")
        found = 0
        while found == 0:
            found = seek(s, "mendiane")
        found = 0
        while found == 0:
            found = seek(s, "mendiane")
        send_and_recv(s, "broadcast 4-5 " + team + str(player_id - 1))
        send_and_recv(s, "broadcast 4-5 " + team + str(player_id - 2))
        send_and_recv(s, "broadcast 4-5 " + team + str(player_id - 3))
        send_cmd(s, "voir")
        cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        if "message" in cmd:
            while "{" not in cmd:
                print RED, 'Received message : ', cmd, STOP
                cmd = string.replace(s.recv(READ_SIZE), '\n', '')
                if "mort" in cmd:
                    sys.exit(PINK + "Vous etes mort" + STOP)
            print RED, 'Received message : ', cmd, STOP
        elif "mort" in cmd:
            sys.exit(PINK + "Vous etes mort" + STOP)
        x, y = voir_analyse(cmd, "joueur joueur joueur joueur")
        while x != 0 and y != 0:
            send_and_recv(s, "broadcast 4-5 " + team + str(player_id - 1))
            send_and_recv(s, "broadcast 4-5 " + team + str(player_id - 2))
            send_and_recv(s, "broadcast 4-5 " + team + str(player_id - 3))
            send_cmd(s, "voir")
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "message" in cmd:
                while "{" not in cmd:
                    print RED, 'Received message : ', cmd, STOP
                    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
                    if "mort" in cmd:
                        sys.exit(PINK + "Vous etes mort" + STOP)
                print RED, 'Received message : ', cmd, STOP
            elif "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
            x, y = voir_analyse(cmd, "joueur joueur joueur joueur")
        clean_square(s)
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose phiras")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "elevation en cours" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort" + STOP)
            elif "ko" in data:
                return 4
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "niveau" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            elif "ko" in data:
                return 4
            data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose mendiane")
        send_and_recv(s, "pose mendiane")
        send_and_recv(s, "pose mendiane")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "elevation en cours" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort" + STOP)
            elif "ko" in data:
                send_and_recv(s, "incantation")
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "niveau" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            elif "ko" in data:
                s.send("incantation\n")
            data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        return 6
    else:
        print CYAN, "I'm a soldier !", STOP
        cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        lf = str(team) + str(player_id)
        global level
        lf2 = str(level) + "-" + str(level + 1)
        while "niveau actuel : 6" not in cmd:
            if lf in cmd and lf2 in cmd:
                handle_broadcast(s, cmd)
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        return 6

def level6(team, s):
    global player_id
    print CYAN, "You're ID is : ", player_id, STOP
    print CYAN, "Waiting...", STOP
    time.sleep(1)
    if (player_id % 6) == 5:
        print CYAN, "I'm a commander !", STOP
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "phiras")
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "linemate")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "deraumere")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "sibur")
        found = 0
        while found == 0:
            found = seek(s, "mendiane")
        found = 0
        while found == 0:
            found = seek(s, "mendiane")
        found = 0
        while found == 0:
            found = seek(s, "phiras")
        found = 0
        while found == 0:
            found = seek(s, "phiras")
        found = 0
        while found == 0:
            found = seek(s, "thystame")
        found = 0
        send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 1))
        send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 2))
        send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 3))
        send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 4))
        send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 5))
        send_cmd(s, "voir")
        cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        if "message" in cmd:
            while "{" not in cmd:
                print RED, 'Received message : ', cmd, STOP
                cmd = string.replace(s.recv(READ_SIZE), '\n', '')
                if "mort" in cmd:
                    sys.exit(PINK + "Vous etes mort" + STOP)
            print RED, 'Received message : ', cmd, STOP
        elif "mort" in cmd:
            sys.exit(PINK + "Vous etes mort" + STOP)
        x, y = voir_analyse(cmd, "joueur joueur joueur joueur joueur joueur")
        while x != 0 and y != 0:
            send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 1))
            send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 2))
            send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 3))
            send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 4))
            send_and_recv(s, "broadcast 6-7 " + team + str(player_id - 5))
            send_cmd(s, "voir")
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
            if "message" in cmd:
                while "{" not in cmd:
                    print RED, 'Received message : ', cmd, STOP
                    cmd = string.replace(s.recv(READ_SIZE), '\n', '')
                    if "mort" in cmd:
                        sys.exit(PINK + "Vous etes mort" + STOP)
                print RED, 'Received message : ', cmd, STOP
            elif "mort" in cmd:
                sys.exit(PINK + "Vous etes mort" + STOP)
            x, y = voir_analyse(cmd, "joueur joueur joueur joueur joueur joueur")
        clean_square(s)
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose phiras")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "elevation en cours" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort" + STOP)
            elif "ko" in data:
                return 6
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "niveau" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            elif "ko" in data:
                return 6
            data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose linemate")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose deraumere")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose sibur")
        send_and_recv(s, "pose mendiane")
        send_and_recv(s, "pose mendiane")
        send_and_recv(s, "pose phiras")
        send_and_recv(s, "pose phiras")
        send_and_recv(s, "pose thystame")
        send_cmd(s, "incantation")
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "elevation en cours" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort" + STOP)
            elif "ko" in data:
                send_and_recv(s, "incantation")
            else:
                data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        data = string.replace(s.recv(READ_SIZE), '\n', '')
        while "niveau" not in data:
            if "mort" in data:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            elif "ko" in data:
                s.send("incantation\n")
            data = string.replace(s.recv(READ_SIZE), '\n', '')
        print RED, 'Received message : ', data, STOP
        return 8
    else:
        print CYAN, "I'm a soldier !", STOP
        cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        lf = str(team) + str(player_id)
        global level
        lf2 = str(level) + "-" + str(level + 1)
        while "niveau actuel : 8" not in cmd:
            if lf in cmd and lf2 in cmd:
                handle_broadcast(s, cmd)
            if "mort" in cmd:
                sys.exit(PINK + "Vous etes mort pendant l'elevation, c'est bete." + STOP)
            cmd = string.replace(s.recv(READ_SIZE), '\n', '')
        return 8

def get_lots_of_food(s, nb):
    for i in range(nb):
        survie(s)

def ia_easy(team, s):
    global level
    while 42:
        if level == 1:
            level = level1(team, s)
        if level == 2:
            survie(s)
            send_and_recv(s, "inventaire")

def ia_medium(team, s):
    global level
    get_lots_of_food(s, 50)
    while 42:
        if level == 1:
            level = level1(team, s)
        if level == 2:
            level = level2(team, s)
        if level == 4:
            level = level4(team, s)
        if level == 6:
            survie(s)
            send_and_recv(s, "inventaire")

def ia_hard(team, s):
    global level
    get_lots_of_food(s, 70)
    while 42:
        if level == 1:
            level = level1(team, s)
        if level == 2:
            level = level2(team, s)
        if level == 4:
            level = level4(team, s)
        if level == 6:
            level = level6(team, s)
        if level == 8:
            sys.exit(PINK + "WP sucker, you win" + STOP)

def ia_badass(team, s):
    roam_info = 0
    while 42:
        roam_info = try_to_kill_all(s, roam_info)

def mob(s):
    while 42:
        seek(s, "nourriture")
        seek(s, "linemate")
        seek(s, "nourriture")
        seek(s, "deraumere")
        seek(s, "nourriture")
        seek(s, "sibur")
        seek(s, "nourriture")
        seek(s, "mendiane")
        seek(s, "nourriture")
        seek(s, "phiras")
        seek(s, "nourriture")
        seek(s, "thystame")

if __name__ == '__main__':
    try:
        team, host, port, ia = parse(len(sys.argv), sys.argv)
    except ValueError as error:
        print PINK, error, STOP
        usage()
        sys.exit(1)
    for res in socket.getaddrinfo(host, port, socket.AF_UNSPEC, socket.SOCK_STREAM):
        af, socktype, proto, canonname, sa = res
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error as msg:
            s = None
            continue
        try:
            s.connect(sa)
        except socket.error as msg:
            s.close()
            s = None
            continue
        break
    if s is None:
        print 'could not open socket'
        sys.exit(1)
    try:
        level = 1
        player_id, map_size = init_cmd(s, team)
        print CYAN, "Player ID = ", player_id, STOP
        time.sleep(1)
        if ia == "random":
            ia_random(team, s)
        elif ia == "easy":
            ia_easy(team, s)
        elif ia == "medium":
            ia_medium(team, s)
        elif ia == "hard":
            ia_hard(team, s)
        elif ia == "badass":
            ia_badass(team, s)
        elif ia == "mob":
            mob(s)
        sys.exit(1)
    except socket.error as error:
        sys.exit(PINK + "Connection ended." + STOP)
    except IndexError:
        sys.exit(PINK + "Server closed" +  STOP)
    except KeyboardInterrupt as error:
        sys.exit(PINK + "\nKeyboard Interrupt" + STOP)
