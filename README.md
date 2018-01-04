# Zappy

## Compile

```bash
make
```

The Makefile will compile the server, the AI, and the graphical client.

## How to run?

### Start the server

run ```zappy_server``` without any arguments to display the usage.<br/>
If you want to start the server with two teams, blue and red, of 10 players, just type:
```bash
./zappy_server -n blue red -c 10
```

### Start the graphical client

```bash
./zappy_graph <ip> <port> (port by default 4242)
```

### Connect the players

You can use the script ```zappy_ai``` to connect one player
```bash
./zappy_ai -n <team_name>
```

If you want the game to be fun to watch, start at least seven or eight players in each team.

### Enjoy

Once everything is set up, you can watch the AI players trying to level up in the Zappy world through the graphical client.
