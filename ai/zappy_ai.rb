#!/usr/bin/env ruby

require 'socket'

DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 4242
DEFAULT_IA = "hard"

def parse(ac, arg)
  if ac < 2 then
    abort('Error : Need at least 2 arguments : "-n" and "teamname')
  end
  i = 0
  host = ""
  port = 0
  team = ""
  ia = ""
  while i < ac do
    if arg[i].include? "-n" then
      team = arg[i + 1]
    elsif arg[i].include? "-p" then
      port = arg[i + 1].to_i
    elsif arg[i].include? "-h" then
      host = arg[i + 1]
    elsif arg[i].include? "-d" then
      ia = arg[i + 1]
    else
      abort("Error : " + arg[i] + " is a wrong entry")
    end
    i += 2
  end
  if team == "" then
    abort("Error : missing -n")
  end
  if host == "" then
    host = DEFAULT_HOST
  end
  if port == 0 then
    port = DEFAULT_PORT
  end
  if ia == "" then
    ia = DEFAULT_IA
  end
  return team, host, port, ia
end

def parse_voir_inv(cmd)
  info = []
  i = 0
  while i < (cmd.length - 2) do
    line = ""
    while i < (cmd.length - 2) and cmd[i] != ',' and cmd[i] != '}' do
      line += cmd[i]
      i += 1
    end
    if cmd[i] == ',' then
      i += 1
    end
    info << line
  end
  return info
end

def calc_front(i)
  n = 1
  if i == 0 then
    return 0
  end
  while (n + 1) ** 2 <= i do
    n += 1
  end
  return n
end

def calc_side(i, front)
  return i - (front ** 2 + front)
end

def parse_clear(square)
  item = []
  i = 0
  while i < square.length do
    line = ""
    while i < square.length and square[i] != ' ' do
      line += square[i]
      i += 1
    end
    if i < square.length then
      i += 1
    end
    item << line
  end
  return item
end

def clean_square(s)
  s.write("voir\n")
  cmd = s.gets
  if not cmd.include? "{" then
    while not cmd.include? "{" do
      if cmd.include? "mort" then
        abort("Vous etes mort")
      end
      cmd = s.gets
    end
  end
  list_square = parse_voir_inv(cmd)
  if list_square.length == 0 then
    return 0
  end
  square = list_square[0]
  if square.include? "joueur " then
    square["joueur "] = ""
  end
  if square.include? "joueur," then
    square["joueur,"] = ""
  end
  if square.include? "nourriture " then
    square["nourriture "] = ""
  end
  if square.include? "nourriture," then
    square["nourriture,"] = ""
  end
  to_clear_list = parse_clear(square)
  for i in 0..(to_clear_list.length - 1)
    send_and_recv(s, "prend " + to_clear_list[i])
  end
end

def voir_analyse(cmd, item)
  if cmd[0] != '{' then
    return nil, nil
  end
  voir_list = parse_voir_inv(cmd)
  for i in 0..(voir_list.length - 1)
    if voir_list[i].include? item then
      front = calc_front(i)
      side = calc_side(i, front)
      return front, side
    end
  end
  return nil, nil
end

def voir_happy_analyse(cmd, item)
  if cmd[0] != '{' then
    return nil, nil
  end
  voir_list = parse_voir_inv(cmd)
  for i in 0..(voir_list.length - 1)
    if voir_list[i].include? item then
      if item == "nourriture" then
        front = calc_front(i)
        side = calc_side(i, front)
        return front, side
      elsif not voir_list[i].include? "joueur" then
        front = calc_front(i)
        side = calc_side(i, front)
        return front, side
      end
    end
  end
  return nil, nil
end

def handle_broadcast(s, cmd)
  if cmd.include? "1," or cmd.include? "2," then
    send_and_recv(s, "avance")
  elsif cmd.include? "3," or cmd.include? "4," then
    send_and_recv(s, "gauche")
    send_and_recv(s, "avance")
  elsif cmd.include? "5," or cmd.include? "6," then
    send_and_recv(s, "gauche")
    send_and_recv(s, "gauche")
    send_and_recv(s, "avance")
  elsif cmd.include? "7," or cmd.include? "8," then
    send_and_recv(s, "droite")
    send_and_recv(s, "avance")
  end
end

def recv_msg(s)
  data = s.gets
  if data.include? "mort" then
    abort("Vous etes mort")
  elsif data.include? "message" then
    while data.include? "message" do
      data = s.gets
    end
  end
end

def send_and_recv(s, cmd)
  s.write(cmd + "\n")
  data = s.gets
  while not data.include? "ok" and not data.include? "ko" do
    if data.include? "mort" then
      abort("Vous etes mort")
    end
    data = s.gets
  end
end

def init_cmd(s, team)
  recv_msg(s)
  s.write(team + "\n")
  p_id = s.gets
  p_id["\n"] = ""
  if p_id.include? "ko" then
    abort("Can't connect to the server : team full or invalid")
  end
  data = s.gets
  data["\n"] = ""
  ret = ""
  i = 0
  while data[i] != ' ' do
    ret += data[i]
    i += 1
  end
  return p_id.to_i, ret.to_i
end

def seek(s, item)
  s.write("voir\n")
  cmd = s.gets
  if cmd.include? "message" then
    while not cmd.include? "{" do
      if cmd.include? "mort" then
        abort("Vous etes mort")
      end
      cmd = s.gets
    end
  elsif cmd.include? "mort" then
    abort("Vous etes mort")
  end
  x, y = voir_happy_analyse(cmd, item)
  if x.nil? then
    send_and_recv(s, "avance")
  else
    for i in 0..(x - 1)
      send_and_recv(s, "avance")
    end
    if y > 0 then
      send_and_recv(s, "droite")
    elsif y < 0 then
      y *= -1
      send_and_recv(s, "gauche")
    end
    for i in 0..(y - 1)
      send_and_recv(s, "avance")
    end
    s.write("prend " + item + "\n")
    data = s.gets
    while 42 do
      if data.include? "ok" then
        return 1
      elsif data.include? "ko" then
        return 0
      else
        data = s.gets
      end
    end
  end
  return 0
end

def roam(s, roam_info)
  if roam_info < $map_size then
    send_and_recv(s, "avance")
    return (roam_info + 1)
  else
    send_and_recv(s, "droite")
    send_and_recv(s, "avance")
    send_and_recv(s, "avance")
    send_and_recv(s, "avance")
    send_and_recv(s, "gauche")
    return (0)
  end
end

def try_to_kill_all(s, roam_info)
  s.write("voir\n")
  cmd = s.gets
  if cmd.include? "message" then
    while not cmd.include? "{" do
      cmd = s.gets
      if cmd.include? "mort" then
        abort("Vous etes mort")
      end
    end
  elsif cmd.include? "mort" then
    abort("Vous etes mort")
  end
  x, y = voir_analyse(cmd, "joueur linemate")
  if x.nil? then
    return roam(s, roam_info)
  else
    for i in 0..(x - 1)
      send_and_recv(s, "avance")
    end
    if y > 0 then
      send_and_recv(s, "droite")
    elsif y < 0 then
      y *= -1
      send_and_recv(s, "gauche")
    end
    for i in 0..(y - 1)
      send_and_recv(s, "avance")
    end
    s.write("voir\n")
    cmd = s.gets
    if cmd.include? "message" then
      while not cmd.include? "{" do
        cmd = s.gets
        if cmd.include? "mort" then
          abort("Vous etes mort")
        end
      end
    elsif cmd.include? "mort" then
      abort("Vous etes mort")
    end
    x, y = voir_analyse(cmd, "joueur joueur linemate")
    if x.nil? then
      return roam(s, roam_info)
    else
      if x == 0 and y == 0 then
        send_and_recv(s, "prend linemate")
        send_and_recv(s, "broadcast J't'ai baiseyy ! <:")
      end
      return roam_info
    end
  end
end

def ia_random(team, s)
  while 42 do
    rand = Random.rand(0..9)
    if rand == 0 then
      send_and_recv(s, "gauche")
      send_and_recv(s, "avance")
    elsif rand == 1 then
      send_and_recv(s, "droite")
      send_and_recv(s, "avance")
    elsif rand == 2 then
      send_and_recv(s, "prend nourriture")
    elsif rand == 3 then
      send_and_recv(s, "prend linemate")
    elsif rand == 4 then
      send_and_recv(s, "prend deraumere")
    elsif rand == 5 then
      send_and_recv(s, "prend sibur")
    elsif rand == 6 then
      send_and_recv(s, "prend mendiane")
    elsif rand == 7 then
      send_and_recv(s, "prend phiras")
    elsif rand == 8 then
      send_and_recv(s, "prend thystame")
    else
      send_and_recv(s, "avance")
    end
  end
end

def survie(s)
  seek(s, "nourriture")
end

def level1(team, s)
  s.write("voir\n")
  cmd = s.gets
  if cmd.include? "message" then
    while not cmd.include? "{" do
      cmd = s.gets
      if cmd.include? "mort" then
        abort("Vous etes mort")
      end
    end
  elsif cmd.include? "mort" then
    abort("Vous etes mort")
  end
  x, y = voir_analyse(cmd, "linemate")
  if x.nil? then
    send_and_recv(s, "avance")
  else
    for i in 0..(x - 1)
      send_and_recv(s, "avance")
    end
    if y > 0 then
      send_and_recv(s, "droite")
    elsif y < 0 then
      y *= -1
      send_and_recv(s, "gauche")
    end
    for i in 0..(y - 1)
      send_and_recv(s, "avance")
    end
    send_and_recv(s, "prend linemate")
    clean_square(s)
    send_and_recv(s, "pose linemate")
    s.write("incantation\n")
    data = s.gets
    if not data.include? "ko" then
      data = s.gets
      while not data.include? "niveau" do
        if data.include? "mort" then
          abort("Vous etes mort")
        elsif data.include? "ko" then
          return 1
        end
        data = s.gets
      end
      return 2
    end
  end
  seek(s, "nourriture")
  return 1
end

def level2(team, s)
  if $player_id % 2 == 1 then
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "phiras")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "phiras")
    end
    send_and_recv(s, "broadcast 2-3 " + team + ($player_id - 1).to_s)
    s.write("voir\n")
    cmd = s.gets
    if cmd.include? "message" then
      while not cmd.include? "message" do
        cmd = s.gets
        if cmd.include? "mort" then
          abort("Vous etes mort")
        end
      end
    elsif cmd.include? "mort" then
      abort("Vous etes mort")
    end
    x, y = voir_analyse(cmd, "joueur joueur")
    while x != 0 and y != 0 do
      send_and_recv(s, "broadcast 2-3 " + team + ($player_id - 1).to_s)
      s.write("voir\n")
      cmd = s.gets
      if cmd.include? "message" then
        while not cmd.include? "{" do
          cmd = s.gets
          if cmd.include? "mort" then
            abort("Vous etes mort")
          end
        end
      elsif cmd.include? "mort" then
        abort("Vous etes mort")
      end
      x, y = voir_analyse(cmd, "joueur joueur")
    end
    clean_square(s)
    send_and_recv(s, "pose linemate")
    send_and_recv(s, "pose deraumere")
    send_and_recv(s, "pose sibur")
    s.write("incantation\n")
    data = s.gets
    while not data.include? "elevation en cours" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        return 2
      else
        data = s.gets
      end
    end
    data = s.gets
    while not data.include? "niveau" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        return 2
      end
      data = s.gets
    end
    send_and_recv(s, "pose linemate")
    send_and_recv(s, "pose linemate")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose phiras")
    send_and_recv(s, "pose phiras")
    s.write("incantation\n")
    data = s.gets
    while not data.include? "elevation en cours" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        send_and_recv(s, "incantation")
      else
        data = s.gets
      end
    end
    data = s.gets
    while not data.include? "niveau" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        s.write("incantation\n")
      end
      data = s.gets
    end
    return 4
  else
    cmd = s.gets
    lf = team + $player_id.to_s
    lf2 = $level.to_s + "-" + ($level + 1).to_s
    while not cmd.include? "niveau actuel : 4" do
      if cmd.include? lf and cmd.include? lf2 then
        handle_broadcast(s, cmd)
      elsif cmd.include? "mort" then
        abort("Vous etes mort pendant l'incantation")
      end
      cmd = s.gets
    end
    return 4
  end
end

def level4(team, s)
  if $player_id % 4 == 3 then
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "phiras")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "mendiane")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "mendiane")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "mendiane")
    end
    send_and_recv(s, "broadcast 4-5 " + team + ($player_id - 1).to_s)
    send_and_recv(s, "broadcast 4-5 " + team + ($player_id - 2).to_s)
    send_and_recv(s, "broadcast 4-5 " + team + ($player_id - 3).to_s)
    s.write("voir\n")
    cmd = s.gets
    if cmd.include? "message" then
      while not cmd.include? "message" do
        cmd = s.gets
        if cmd.include? "mort" then
          abort("Vous etes mort")
        end
      end
    elsif cmd.include? "mort" then
      abort("Vous etes mort")
    end
    x, y = voir_analyse(cmd, "joueur joueur joueur joueur")
    while x != 0 and y != 0 do
      send_and_recv(s, "broadcast 4-5 " + team + ($player_id - 1).to_s)
      send_and_recv(s, "broadcast 4-5 " + team + ($player_id - 2).to_s)
      send_and_recv(s, "broadcast 4-5 " + team + ($player_id - 3).to_s)
      s.write("voir\n")
      cmd = s.gets
      if cmd.include? "message" then
        while not cmd.include? "{" do
          cmd = s.gets
          if cmd.include? "mort" then
            abort("Vous etes mort")
          end
        end
      elsif cmd.include? "mort" then
        abort("Vous etes mort")
      end
      x, y = voir_analyse(cmd, "joueur joueur joueur joueur")
    end
    clean_square(s)
    send_and_recv(s, "pose linemate")
    send_and_recv(s, "pose deraumere")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose phiras")
    s.write("incantation\n")
    data = s.gets
    while not data.include? "elevation en cours" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        return 4
      else
        data = s.gets
      end
    end
    data = s.gets
    while not data.include? "niveau" do
      if data.include? "mort" then
        abort("Vous etes mort pendant l'incantation")
      elsif data.include? "ko" then
        return 4
      end
      data = s.gets
    end
    send_and_recv(s, "pose linemate")
    send_and_recv(s, "pose deraumere")
    send_and_recv(s, "pose deraumere")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose mendiane")
    send_and_recv(s, "pose mendiane")
    send_and_recv(s, "pose mendiane")
    s.write("incantation\n")
    data = s.gets
    while not data.include? "elevation en cours" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        send_and_recv(s, "incantation")
      else
        data = s.gets
      end
    end
    data = s.gets
    while not data.include? "niveau" do
      if data.include? "mort" then
        abort("Vous etes mort pendant l'incantation")
      elsif data.include? "ko" then
        s.write("incantation\n")
      end
      data = s.gets
    end
    return 6
  else
    cmd = s.gets
    lf = team + $player_id.to_s
    lf2 = $level.to_s + "-" + ($level + 1).to_s
    while not cmd.include? "niveau actuel : 6" do
      if cmd.include? lf and cmd.include? lf2 then
        handle_broadcast(s, cmd)
      elsif cmd.include? "mort" then
        abort("Vous etes mort pendant l'incantation")
      end
      cmd = s.gets
    end
    return 6
  end
end

def level6(team, s)
  if $player_id % 6 == 5 then
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "phiras")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "linemate")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "deraumere")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "sibur")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "mendiane")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "mendiane")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "phiras")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "phiras")
    end
    lf = 0
    while lf == 0 do
      lf = seek(s, "thystame")
    end
    send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 1).to_s)
    send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 2).to_s)
    send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 3).to_s)
    send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 4).to_s)
    send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 5).to_s)
    s.write("voir\n")
    cmd = s.gets
    if cmd.include? "message" then
      while not cmd.include? "{" do
        cmd = s.gets
        if cmd.include? "mort" then
          abort("Vous etes mort")
        end
      end
    elsif cmd.include? "mort" then
      abort("Vous etes mort")
    end
    x, y = voir_analyse(cmd, "joueur joueur joueur joueur joueur joueur")
    while x != 0 and y != 0 do
      send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 1).to_s)
      send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 2).to_s)
      send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 3).to_s)
      send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 4).to_s)
      send_and_recv(s, "broadcast 6-7 " + team + ($player_id - 5).to_s)
      s.write("voir\n")
      cmd = s.gets
      if cmd.include? "message" then
        while not cmd.include? "{" do
          cmd = s.gets
          if cmd.include? "mort" then
            abort("Vous etes mort")
          end
        end
      elsif cmd.include? "mort" then
        abort("Vous etes mort")
      end
      x, y = voir_analyse(cmd, "joueur joueur joueur joueur joueur joueur")
    end
    clean_square(s)
    send_and_recv(s, "pose linemate")
    send_and_recv(s, "pose deraumere")
    send_and_recv(s, "pose deraumere")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose sibur")
    send_and_recv(s, "pose phiras")
    s.write("incantation\n")
    data = s.gets
    while not data.include? "elevation en cours" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        return 6
      else
        data = s.gets
      end
    end
    data = s.gets
    while not data.include? "niveau" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        return 6
      end
      data = s.gets
    end
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
    s.write("incantation\n")
    data = s.gets
    while not data.include? "elevation en cours" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        send_and_recv(s, "incantation")
      else
        data = s.gets
      end
    end
    data = s.gets
    while not data.include? "niveau" do
      if data.include? "mort" then
        abort("Vous etes mort")
      elsif data.include? "ko" then
        s.write("incantation\n")
      end
      data = s.gets
    end
    return 8
  else
    cmd = s.gets
    lf = team + $player_id.to_s
    lf2 = $level.to_s + "-" + ($level + 1).to_s
    while not cmd.include? "niveau actuel : 8" do
      if cmd.include? lf and cmd.include? lf2 then
        handle_broadcast(s, cmd)
      elsif cmd.include? "mort" then
        abort("Vous etes mort pendant l'incantation")
      end
      cmd = s.gets
    end
    return 8
  end
end

def get_lots_of_food(s, nb)
  for i in 0..(nb - 1)
    survie(s)
  end
end

def ia_easy(team, s)
  while 42 do
    if $level == 1 then
      $level = level1(team, s)
    end
    if $level == 2 then
      survie(s)
    end
  end
end

def ia_medium(team, s)
  get_lots_of_food(s, 100)
  while 42 do
    if $level == 1 then
      $level = level1(team, s)
    end
    if $level == 2 then
      $level = level2(team, s)
    end
    if $level == 4 then
      $level = level4(team, s)
    end
    if $level == 6 then
      survie(s)
    end
  end
end

def ia_hard(team, s)
  get_lots_of_food(s, 120)
  while 42 do
    if $level == 1 then
      $level = level1(team, s)
    end
    if $level == 2 then
      $level = level2(team, s)
    end
    if $level == 4 then
      $level = level4(team, s)
    end
    if $level == 6 then
      $level = level6(team, s)
    end
    if $level == 8 then
      abort("WP sucker, you win")
    end
  end
end

def ia_badass(team, s)
  roam_info = 0
  while 42 do
    roam_info = try_to_kill_all(s, roam_info)
  end
end

def mob(s)
  while 42 do
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
  end
end

if __FILE__ == $PROGRAM_NAME
  begin
    team, host, port, ia = parse(ARGV.size, ARGV)
    s = TCPSocket.new host, port
    $level = 1
    $player_id, $map_size = init_cmd(s, team)
    if ia == "hard" then
      ia_hard(team, s)
    elsif ia == "medium" then
      ia_medium(team, s)
    elsif ia == "easy" then
      ia_easy(team, s)
    elsif ia == "random" then
      ia_random(team, s)
    elsif ia == "badass" then
      ia_badass(team, s)
    elsif ia == "mob" then
      mob(s)
    end
  rescue NoMethodError
    abort("Connection reset by peer")
  rescue => e
    abort(e.message)
  rescue Interrupt
    abort("\nKeyboard Interrupt")
  end
end
