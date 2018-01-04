import sys
import argparse

def     check_ip(parser, ip):
    sip = ip.split('.')
    ip_err = sys.argv[0][2:] + ': error: argument -i/--ip: invalid ip address: \'' + ip + '\''
    if len(sip) != 4:
        parser.print_usage()
        print ip_err
        sys.exit(0)
    for elem in sip:
        if not elem.isdigit():
            parser.print_usage()
            print(ip_err)
            sys.exit(0)

def     parse():
    parser = argparse.ArgumentParser(description='A simple interface for the {EPITECH.} Zappy project.')
    parser.add_argument('-i', '--ip', default='127.0.0.1', help="The server's ip (optionnal)")
    parser.add_argument('-p', '--port', type=int, default='4242', help="The server's port (optionnal)")
    parser.add_argument('-n', '--name', required=True, help="The team you want to be on (required)")

    args = parser.parse_args()
    check_ip(parser, args.ip)
    return args
