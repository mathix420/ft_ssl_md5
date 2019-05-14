# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agissing <agissing@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/10 14:00:52 by agissing          #+#    #+#              #
#    Updated: 2019/04/16 15:11:47 by agissing         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# ***                                FT_SSL                                *** #
# **************************************************************************** #

################################################################################
#####                              FILES VARS                              #####
################################################################################

SSL               = ft_ssl

#main dirs
SSL_DIR           = ssl/
MD5_DIR           = md5/
SHA256_DIR        = sha256/
SHA512_DIR        = sha512/
WHIRLPOOL_DIR     = whirlpool/

MAIN_DIR_OBJ      = obj/
SSL_DIR_OBJ       = $(MAIN_DIR_OBJ)$(SSL_DIR)
MD5_DIR_OBJ       = $(MAIN_DIR_OBJ)$(MD5_DIR)
SHA256_DIR_OBJ    = $(MAIN_DIR_OBJ)$(SHA256_DIR)
SHA512_DIR_OBJ    = $(MAIN_DIR_OBJ)$(SHA512_DIR)
WHIRLPOOL_DIR_OBJ = $(MAIN_DIR_OBJ)$(WHIRLPOOL_DIR)

#includes
SSL_INC			  = includes/
MD5_INC           = $(MD5_DIR)includes/
SHA256_INC        = $(SHA256_DIR)includes/
SHA512_INC        = $(SHA512_DIR)includes/
WHIRLPOOL_INC     = $(WHIRLPOOL_DIR)includes/

#includes
#{{AUTO-SRC}path=includes;file=*.h;name=_SRC_INCLUDES}
_SRC_INCLUDES = ft_ssl.h
#{END}

#ssl
#{{AUTO-SRC}path=ssl;file=*.c;name=_SRC_SSL}
_SRC_SSL = check_param.c \
error.c \
ft_libft.c \
main.c \
parser.c
#{END}
SRC_SSL = $(addprefix $(SSL_DIR),$(_SRC_SSL))
OBJ_SSL = $(addprefix $(SSL_DIR_OBJ),$(_SRC_SSL:.c=.o))

#md5
#{{AUTO-SRC}path=md5;file=*.c;name=_SRC_MD5}
_SRC_MD5 = data.c \
libfct.c \
main.c
#{END}
SRC_MD5 = $(addprefix $(MD5_DIR),$(_SRC_MD5))
OBJ_MD5 = $(addprefix $(MD5_DIR_OBJ),$(_SRC_MD5:.c=.o))

#sha256
#{{AUTO-SRC}path=sha256;file=*.c;name=_SRC_SHA256}
_SRC_SHA256 = 
#{END}
SRC_SHA256 = $(addprefix $(SHA256_DIR),$(_SRC_SHA256))
OBJ_SHA256 = $(addprefix $(SHA256_DIR_OBJ),$(_SRC_SHA256:.c=.o))

#sha512
#{{AUTO-SRC}path=sha512;file=*.c;name=_SRC_SHA512}
_SRC_SHA512 = 
#{END}
SRC_SHA512 = $(addprefix $(SHA512_DIR),$(_SRC_SHA512))
OBJ_SHA512 = $(addprefix $(SHA512_DIR_OBJ),$(_SRC_SHA512:.c=.o))

#whirlpool
#{{AUTO-SRC}path=whirlpool;file=*.c;name=_SRC_WHIRLPOOL}
_SRC_WHIRLPOOL = 
#{END}
SRC_WHIRLPOOL = $(addprefix $(WHIRLPOOL_DIR),$(_SRC_WHIRLPOOL))
OBJ_WHIRLPOOL = $(addprefix $(WHIRLPOOL_DIR_OBJ),$(_SRC_WHIRLPOOL:.c=.o))

#global sources
SRCS   = $(SRC_SSL) $(SRC_MD5) $(SRC_SHA256) $(SRC_SHA512) $(SRC_WHIRLPOOL)
#global objects
OBJS   = $(OBJ_SSL) $(OBJ_MD5) $(OBJ_SHA256) $(OBJ_SHA512) $(OBJ_WHIRLPOOL)
#global include
INCS   = $(SSL_INC) $(MD5_INC) $(SHA256_INC) $(SHA512_INC) $(WHIRLPOOL_DIR)

################################################################################
#####                           COMPILER OPTIONS                           #####
################################################################################

CC    = gcc
FLAGS = -Wall -Wextra -Werror
OPTS  = $(foreach d, $(INCS), -I$d) -g3

################################################################################
#####                            MAKEFILE RULES                            #####
################################################################################

.PHONY : all clean fclean re norm

all : $(SSL)

norm :
	@norminette $(SRCS) $(INCS)

update :
	@python3 auto_src.py Makefile
	@echo "\033[35m[SRC]\033[0m Sources added"
	@make $(SSL)

#creating asm objects
$(MAIN_DIR_OBJ)%.o : %.c $(INCS) Makefile
	@if test ! -d $(dir $@); \
	then \
		mkdir -p $(dir $@); \
		printf "\e[94m[OBJ]\e[0m Directory created!\n"; \
	fi
	@$(CC) $(FLAGS) -c $< -o $@ $(OPTS)
	@printf "\e[2K \e[32m[CC]\e[0m %-15s\r" "$<"

#creating asm
$(SSL) : $(OBJS) $(INCS) Makefile
	@$(CC) $(FLAGS) $(OBJS) -o $@ $(OPTS)
	@printf "\e[2K\e[94m[PRG]\e[0m $@ done!\n\r"

#cleaning
clean :
	@/bin/rm -rf $(MAIN_DIR_OBJ)
	@echo "\033[33m[PRG]\033[0m Cleaning done"

#deep cleaning
fclean :
	@/bin/rm -rf $(MAIN_DIR_OBJ)
	@/bin/rm -f $(SSL)
	@echo "\033[31m[PRG]\033[0m Cleaning done"

#recompile all
re : fclean all
