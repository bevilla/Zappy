import select
from parser import parse
from ia import IA
from ia_socket import IA_Socket

def     main():
    args = parse()
    ia1 = IA(host=args.ip, port=args.port, name=args.name, verbose=True)
    ia1.run()
