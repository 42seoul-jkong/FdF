# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 13:20:43 by jkong             #+#    #+#              #
#    Updated: 2022/04/18 13:20:43 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o .h
.PHONY: all clean fclean re bonus dclean

CC = cc
RM = rm -f

OBJECTS_DIR = objs/

SRCS_BASE = app.c libft.c libft_split.c
OBJS_BASE = $(addprefix $(OBJECTS_DIR), $(SRCS_BASE:.c=.o))
HEADER_BASE = fdf.h

SRCS_GNL = get_next_line.c get_next_line_utils.c
OBJS_GNL = $(addprefix $(OBJECTS_DIR), $(SRCS_GNL:.c=.o))
HEADER_GNL = get_next_line.h

TARGET = fdf
SRCS = $(SRCS_BASE) $(SRCS_GNL)
OBJS = $(OBJS_BASE) $(OBJS_GNL)

#DEP_DIR = minilibx_macos
#DEP_NAME = libmlx.a
#DEP_HOOK = 
DEP_DIR = minilibx
DEP_NAME = libmlx.dylib
DEP_HOOK = INC=-I. INC+=-O

LDFLAGS += -lm
LDFLAGS += -L$(DEP_DIR) -lmlx -framework OpenGL -framework AppKit

C_SANITIZER_FLAGS = address undefined
CFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
LDFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))

C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))

C_DEBUG_FLAGS = g3
CFLAGS += $(addprefix -, $(C_DEBUG_FLAGS))

all: $(TARGET)
clean: dclean			;	$(RM) -r $(OBJECTS_DIR)
fclean: clean			;	$(RM) $(TARGET) $(TARGET_BONUS)
re: fclean all
bonus: all

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS): | $(OBJECTS_DIR)

$(OBJS_BASE): $(HEADER_BASE)

$(OBJS_GNL): $(HEADER_GNL)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS) | $(DEP_NAME)
	$(CC) -o $@ $(LDFLAGS) $^

dclean:
	$(RM) $(DEP_NAME)
	$(MAKE) -C $(DEP_DIR) clean

$(DEP_NAME):
	$(MAKE) -C $(DEP_DIR) all $(DEP_HOOK)
	cp $(DEP_DIR)/$(DEP_NAME) .
