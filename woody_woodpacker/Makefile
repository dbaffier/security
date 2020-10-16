# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 00:18:28 by dbaffier          #+#    #+#              #
#    Updated: 2019/12/12 23:56:22 by dbaffier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WOODY = woody_woodpacker

CFLAGS += -Wall -Werror -Wextra -g -fomit-frame-pointer

INC_DIR = inc/
INCS = -I$(INC_DIR)

OBJS_C_DIR = objs_c/
OBJS_C = $(addprefix $(OBJS_C_DIR), $(SRCS_C:.c=.o))

OBJS_S_DIR = objs_s/
OBJS_S = $(addprefix $(OBJS_S_DIR), $(SRCS_S:.s=.o))

OBJS_MACHO_DIR = objs_c/mach-o/
OBJS_MACHO = $(addprefix $(OBJS_MACHO_DIR), $(SRCS_MACHO:.c=.o))

OBJS_TOOLS_DIR = objs_tools/
OBJS_TOOLS = $(addprefix $(OBJS_TOOLS_DIR), $(SRCS_TOOLS:.c=.o))

C_DIR = c/
SRCS_C =	main.c					\
			err.c					\
			integrity.c				\
			parse_flag.c			\

ASM_DIR = asm/
SRCS_S = infect.s					\
			rc4.s					\

MACHO_DIR = c/mach-o/
SRCS_MACHO = macho_info.c			\
				encrypt_macho64.c	\
				macho.c				\

TOOLS_DIR = tools/
SRCS_TOOLS = tools.c				\

all: $(OBJS_C_DIR) $(OBJS_S_DIR) $(OBJS_MACHO_DIR) $(OBJS_TOOLS_DIR) $(WOODY)

$(OBJS_S_DIR):
	@mkdir -p $@

$(OBJS_MACHO_DIR):
	@mkdir -p $@

$(OBJS_C_DIR):
	@mkdir -p $@

$(OBJS_TOOLS_DIR):
	@mkdir -p $@

$(WOODY): $(OBJS_C) $(OBJS_S) $(OBJS_TOOLS) $(OBJS_MACHO)
	gcc -fsanitize=address $^ -o $@

$(OBJS_TOOLS_DIR)%.o: $(TOOLS_DIR)%.c
	gcc $(CFLAGS) -o $@ -c $< $(INCS)

$(OBJS_C_DIR)%.o: $(C_DIR)%.c
	gcc $(CFLAGS) -o $@ -c $< $(INCS)

$(OBJS_S_DIR)%.o: $(ASM_DIR)%.s
	nasm -f macho64 -o $@ $<

clean:
	rm -rf $(OBJS_TOOLS_DIR)
	rm -rf $(OBJS_C_DIR)
	rm -rf $(OBJS_S_DIR)

fclean: clean
	rm -f $(LIBFT_LIB)
	rm -f $(WOODY)

re: fclean all

.PHONY: fclean all clean re
