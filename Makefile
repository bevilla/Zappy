##
## Makefile for zappy in /home/bevill_a/rendu/PSU_2014_zappy
##
## Made by Alexis Bevillard
## Login   <bevill_a@epitech.net>
##
## Started on  Tue May 19 09:56:11 2015 Alexis Bevillard
## Last update Sun Jul  5 22:11:13 2015 Louis Bouteillon
##

NAME =		zappy_server
NAME2 =		zappy_ai
NAME3 =		zappy_graph
NAME4 =		zappy_gui

SRV_DIR =	./server/
AI_DIR = 	./ai/
GR_DIR =	./graph/
GUI_DIR =	./gui/

#AUDIO_LIB =	SFML_Audio/lib
#AUDIO_INC =	SFML_Audio/include

SRC_DIR =	$(SRV_DIR)src/
OBJ_DIR =	$(SRV_DIR)objs/
UTILS_DIR =	$(SRC_DIR)utils/
SERVER_DIR =	$(SRC_DIR)server/
CLIENT_DIR =	$(SRC_DIR)client/
GRAPHIC_DIR =	$(SRC_DIR)graphic/
INC_DIR =	$(SRV_DIR)inc/

AI_EXEC =	zappy_ai.rb

GR_SRC_DIR =	$(GR_DIR)src/
GOBJ_DIR =	$(GR_DIR)objs/
GR_INC_DIR =	$(GR_DIR)inc/
#SFML_LIB_DIR =	$(GR_DIR)SFML-2.2/lib/
GLEW_LIB_DIR =	$(GR_DIR)glew-1.10.0/lib/
#SFML_INC_DIR =	$(GR_DIR)SFML-2.2/include/
GLEW_INC_DIR =	$(GR_DIR)glew-1.10.0/include/

GUI_EXEC =	zappy_gui.py

SRCS =		$(SRC_DIR)main.c \
		$(SERVER_DIR)parse_num_options.c \
		$(SERVER_DIR)server_error.c \
		$(SERVER_DIR)new_message.c \
		$(SERVER_DIR)zappy_parse.c \
		$(SERVER_DIR)player_exec.c \
		$(SERVER_DIR)speed_mode.c \
		$(SERVER_DIR)new_client.c \
		$(SERVER_DIR)init_zappy.c \
		$(SERVER_DIR)init_exec.c \
		$(SERVER_DIR)end_zappy.c \
		$(SERVER_DIR)server.c \
		$(SERVER_DIR)update.c \
		$(SERVER_DIR)remove.c \
		$(SERVER_DIR)action.c \
		$(CLIENT_DIR)cmd_connect_nbr.c \
		$(CLIENT_DIR)cmd_incantation.c \
		$(CLIENT_DIR)cmd_broadcast.c \
		$(CLIENT_DIR)cmd_direction.c \
		$(CLIENT_DIR)cmd_expulse.c \
		$(CLIENT_DIR)append_voir.c \
		$(CLIENT_DIR)client_comm.c \
		$(CLIENT_DIR)cmd_items.c \
		$(CLIENT_DIR)cmd_fork.c \
		$(CLIENT_DIR)cmd_mort.c \
		$(CLIENT_DIR)cmd_voir.c \
		$(CLIENT_DIR)player.c \
		$(GRAPHIC_DIR)graphic_auto_power.c \
		$(GRAPHIC_DIR)graphic_auto_items.c \
		$(GRAPHIC_DIR)graphic_auto_meta.c \
		$(GRAPHIC_DIR)graphic_auto_cmd.c \
		$(GRAPHIC_DIR)get_graphic_args.c \
		$(GRAPHIC_DIR)send_to_graphics.c \
		$(GRAPHIC_DIR)graphic_auto_egg.c \
		$(GRAPHIC_DIR)graphic_cmd_arg.c \
		$(GRAPHIC_DIR)graphic_exec.c \
		$(GRAPHIC_DIR)graphic_cmd.c \
		$(UTILS_DIR)epur_str.c \
		$(UTILS_DIR)isnum.c \
		$(UTILS_DIR)list2.c \
		$(UTILS_DIR)c_buf.c \
		$(UTILS_DIR)list.c \
		$(UTILS_DIR)sig.c \
		$(UTILS_DIR)msg.c

GR_SRCS =	$(GR_SRC_DIR)main.cpp \
		$(GR_SRC_DIR)Window.cpp \
		$(GR_SRC_DIR)Map.cpp \
		$(GR_SRC_DIR)Cell.cpp \
		$(GR_SRC_DIR)Camera.cpp \
		$(GR_SRC_DIR)Player.cpp \
		$(GR_SRC_DIR)ZappyClient.cpp \
		$(GR_SRC_DIR)ParseCmd.cpp \
		$(GR_SRC_DIR)ChatBox.cpp \
		$(GR_SRC_DIR)Inventory.cpp \
		$(GR_SRC_DIR)Broadcast.cpp \
		$(GR_SRC_DIR)Time.cpp

OBJS =		$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRCS:.c=.o))

GR_OBJS =	$(patsubst $(GR_SRC_DIR)%, $(GOBJ_DIR)%, $(GR_SRCS:.cpp=.o))

CFLAGS =	-Wall -Wextra -Werror -ansi -pedantic -I$(INC_DIR) -std=c99 -g3

LDFLAGS =	-lm

CPPFLAGS +=	-I$(GR_INC_DIR) -I$(GLEW_INC_DIR) -I$(SFML_INC_DIR) -I$(AUDIO_INC)
CPPFLAGS +=	-O3 -Wall -Wextra -W -g3 -std=c++11

GR_LDFLAGS +=	-L$(GLEW_LIB_DIR) -lGLEW
GR_LDFLAGS +=	-lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
GR_LDFLAGS +=	-Wl,-rpath=$(GLEW_LIB_DIR)


C_COMPILE =	gcc -c
CPP_COMPILE =	g++ -c
C_LINK =	gcc -o
CPP_LINK =	g++ -o
MKDIR =		mkdir -p
RM =		rm -rfv
ECHO_GREEN =	echo -e "\033[32m"
END_OF_ECHO =	"\033[0m"
CP =		cp

all:		$(NAME) $(NAME2) $(NAME3) $(NAME4)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@$(MKDIR) $(dir $@)
		@$(C_COMPILE) $< $(CFLAGS) -o $@
		@echo $(patsubst $(SRC_DIR)%, %, $<) compiled

$(GOBJ_DIR)%.o:	$(GR_SRC_DIR)%.cpp
		@$(MKDIR) $(dir $@)
		@$(CPP_COMPILE) $< $(CPPFLAGS) -o $@
		@echo $(patsubst $(GR_SRC_DIR)%, %, $<) compiled

$(NAME):	$(OBJS)
		@$(C_LINK) $(NAME) $(OBJS) $(LDFLAGS)
		@$(ECHO_GREEN)[OK] $(NAME) linked $(END_OF_ECHO)

$(NAME2):
		@$(CP) $(AI_DIR)$(AI_EXEC) $(NAME2)
		@$(ECHO_GREEN)[OK] $(NAME2) linked $(END_OF_ECHO)

$(NAME3):	$(GR_OBJS)
		@$(CPP_LINK) $(NAME3) $(GR_OBJS) $(GR_LDFLAGS)
		@$(ECHO_GREEN)[OK] $(NAME3) linked $(END_OF_ECHO)

$(NAME4):
		@$(CP) $(GUI_DIR)$(GUI_EXEC) $(NAME4)
		@$(ECHO_GREEN)[OK] $(NAME4) linked $(END_OF_ECHO)

clean:
		@$(RM) $(OBJ_DIR)
		@$(RM) $(GOBJ_DIR)
		@$(ECHO_GREEN)[OK] Every objects have been removed $(END_OF_ECHO)

fclean:		clean
		@$(RM) $(NAME) $(NAME2) $(NAME3) $(NAME4)
		@$(ECHO_GREEN)[OK] $(NAME) removed $(END_OF_ECHO)
		@$(ECHO_GREEN)[OK] $(NAME2) removed $(END_OF_ECHO)
		@$(ECHO_GREEN)[OK] $(NAME3) removed $(END_OF_ECHO)
		@$(ECHO_GREEN)[OK] $(NAME4) removed $(END_OF_ECHO)

re:		fclean all

.PHONY:		all clean fclean re
