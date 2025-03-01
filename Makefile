MAKEFLAGS			:= --no-print-directory
.DEFAULT_GOAL		:= all

.DELETE_ON_ERROR:
.SECONDEXPANSION:

#=================================COMPILATION==================================#
CC					:= g++
CPPFLAGS			:= -g -std=c++20 -MP -MMD -I SFML-3/include -I srcs
LIBFSMLFLAG			:= -L SFML-3/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,\$$ORIGIN/SFML-3/lib

#=====================================NAME=====================================#
NAME				:= snake

#==================================DIRECTORIES=================================#
BUILD				:= build

#====================================TARGETS===================================#
SRCS				:=	srcs/main.cpp \
						srcs/parser.cpp \
						srcs/Environment/Environment.cpp \
						srcs/Environment/Grid.cpp \
						srcs/Visual/Visual.cpp

OBJS 				:= ${SRCS:srcs/%.cpp=$(BUILD)/%.o}
DEPS				:= $(SRCS:srcs/%.cpp=$(BUILD)/%.d)
DIRS				:= $(sort $(shell dirname $(BUILD) $(OBJS)))

#====================================COLORS====================================#
NOC					:= \033[0m
BOLD				:= \033[1m
UNDERLINE			:= \033[4m
BLINK				:= \e[5m
BLACK				:= \033[1;30m
RED					:= \e[1m;31m;
GREEN				:= \e[1m;32m;
YELLOW				:= \e[1m;33m;
RED					:= \e[1m\e[38;5;196m
GREEN				:= \e[1m\e[38;5;76m
YELLOW				:= \e[1m\e[38;5;220m
BLUE				:= \e[1m\e[38;5;33m
VIOLET				:= \033[1;35m
CYAN				:= \033[1;36m
WHITE				:= \033[1;37m

#=================================COUNTER UTILS================================#
NB_COMPIL			:= 0

ifndef	RECURSIVE
TOTAL_COMPIL		:= $(shell expr $$(make -n RECURSIVE=1 | grep $(CC) | wc -l) - 1)
endif
ifndef TOTAL_COMPIL
TOTAL_COMPIL		:= $(words $(OBJS))
endif

#=====================================RULES====================================#
$(DIRS):
	@mkdir $@

$(OBJS) : $(BUILD)/%.o : srcs/%.cpp | $$(@D)
	$(if $(filter $(NB_COMPIL),0), @echo "$(BLUE)Compiling$(NOC)")
	$(eval NB_COMPIL=$(shell expr $(NB_COMPIL) + 1))
	@echo "$(WHITE)[$(NB_COMPIL)/$(TOTAL_COMPIL)] $(VIOLET)Compiling $< $(NOC)"
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BLUE)Creation of binary$(NOC)"
	@g++ $^ $(LIBFSMLFLAG) -o $(NAME)
	@echo "$(GREEN)Done$(NOC)"

all : $(NAME)

clean :
	@echo "$(RED)Deleting objects$(NOC)"
	@rm -rf $(BUILD) 2>/dev/null || echo -n

fclean : clean
	@echo "$(RED)Deleting binary$(NOC)"
	@rm -f $(NAME)

re :
	@clear -x
	@make fclean
	@make

run: $(NAME)
	@./$(NAME)

.PHONY : $(NAME) all clean fclean re run

-include $(DEPS)