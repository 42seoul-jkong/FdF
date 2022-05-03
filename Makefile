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
.PHONY: all clean fclean re bonus dclean release

CC = cc
RM = rm -f

OBJECTS_DIR = objs/

SRCS_BASE = app.c \
			fdf_map.c fdf_map_read.c \
			fdf_draw.c \
			fdf_input.c fdf_input_key.c fdf_input_mouse.c fdf_input_move.c \
			draw.c draw_line.c depth.c \
			coordinate.c transform.c color.c \
			libft.c libft_split.c libft_strtoi.c \
			util_flag.c \
			safe_mem.c safe_write.c
OBJS_BASE = $(addprefix $(OBJECTS_DIR), $(SRCS_BASE:.c=.o))
HEADER_BASE = fdf.h

SRCS_GNL = get_next_line.c get_next_line_utils.c
OBJS_GNL = $(addprefix $(OBJECTS_DIR), $(SRCS_GNL:.c=.o))
HEADER_GNL = get_next_line.h

TARGET = fdf
SRCS = $(SRCS_BASE) $(SRCS_GNL)
OBJS = $(OBJS_BASE) $(OBJS_GNL)

MLX = mlx
ifeq ($(shell uname), Linux)
	MLX_TYPE = a
	MLX_DIR = minilibx-linux
	MLX_DEP = -lXext -lX11
else
	MLX_TYPE = dylib
	MLX_DIR = minilibx_mms_20210621
	MLX_HOOK = OPTI=-Ounchecked
endif
MLX_NAME = lib$(MLX).$(MLX_TYPE)

LDFLAGS += -lm
CFLAGS += -I$(MLX_DIR)
LDFLAGS += -L$(MLX_DIR) -l$(MLX) $(MLX_DEP)

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
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS) | $(MLX_NAME)
	$(CC) -o $@ $^ $(LDFLAGS)

dclean:
	$(RM) $(MLX_NAME)
	$(MAKE) -C $(MLX_DIR) clean

release: C_SANITIZER_FLAGS=
release: C_DEBUG_FLAGS=
release: CFLAGS+=-O3
release: all

$(MLX_NAME):
	$(MAKE) -C $(MLX_DIR) all $(MLX_HOOK)
	cp $(MLX_DIR)/$(MLX_NAME) .
