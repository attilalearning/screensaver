CC									=	cc
CFLAGS							=	-Wall -Wextra -Werror -g
VFLAGS							=	--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt
AR									=	ar rcs
RM									=	rm -f
RM_DIR							=	rm -rf

$(eval CURR_DIR			=	$(shell pwd))

BIN_DIR							=	./bin
NAME								=	$(BIN_DIR)/screensaver

LIB_DIR							= ./lib

LIBFT_DIR						=	$(LIB_DIR)/libft
LIBFT_A							=	$(LIBFT_DIR)/lib/libft.a

MLX_DIR							=	$(LIB_DIR)/mlx_linux
LIBMLX_A						=	$(MLX_DIR)/libmlx.a

SRCS_DIR						=	./srcs
SRCS_COLORS_DIR			=	$(SRCS_DIR)/colors
SRCS_CONTROLS_DIR		=	$(SRCS_DIR)/controls
SRCS_GRAPHICS_DIR		=	$(SRCS_DIR)/graphics
SRCS_RENDERERS_DIR	=	$(SRCS_DIR)/renderers
ALL_SRCS_DIRS				=	$(SRCS_DIR) \
											$(SRCS_COLORS_DIR) \
											$(SRCS_CONTROLS_DIR) \
											$(SRCS_GRAPHICS_DIR) \
											$(SRCS_RENDERERS_DIR)

OBJS_DIR						=	./obj

SRCS_FILES					=	\
				$(addprefix $(SRCS_DIR)/, \
					cleanup.c \
					init.c \
					main.c \
					show_error.c \
				) \
				$(addprefix $(SRCS_COLORS_DIR)/, \
					change_color.c \
					color_2_argb.c \
					color_2_int.c \
					color_add.c \
				) \
				$(addprefix $(SRCS_CONTROLS_DIR)/, \
					is_control_key.c \
					key_handler.c \
					mouse_click_handler.c \
					set_key_dir.c \
				) \
				$(addprefix $(SRCS_GRAPHICS_DIR)/, \
					put_cross.c \
					put_fps.c \
					put_pixel.c \
				) \
				$(addprefix $(SRCS_RENDERERS_DIR)/, \
					fix_if_out_of_bound.c \
					render_one_pixel_at_a_time.c \
					render_one_pixel_at_a_time_in_a_direction_loop.c \
					render_small_or_large_frame_at_a_time.c \
					set_renderer.c \
				)

OBJS_FILES					=	$(subst $(SRCS_DIR)/,$(OBJS_DIR)/,$(SRCS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT_A) $(LIBMLX_A) $(OBJS_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $@

test:
	@echo $(SRCS_DIR)
	@echo $(SRCS_FILES)
	@ls -la $(SRCS_FILES)
	@echo $(OBJS_DIR)
	@echo $(OBJS_FILES)
	@-ls -la $(OBJS_FILES)
	@echo CURR_DIR=\"$(CURR_DIR)\"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) \
		$(subst $(SRCS_DIR)/,$(OBJS_DIR)/,$(ALL_SRCS_DIRS))

$(LIBFT_A): | $(LIB_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX_A): | $(LIB_DIR)
	cd $(MLX_DIR); ./configure
	$(MAKE) -C $(MLX_DIR)

$(LIB_DIR):
	mkdir -p $(LIBFT_DIR) $(MLX_DIR)
	git submodule update --init --recursive

valgrind:
	valgrind $(VFLAGS) ./$(NAME)

clean:
ifneq ("$(OBJS_DIR)",".")
	$(RM_DIR) $(OBJS_DIR)
else
	@echo Refusing to delete/clear OBJS_DIR as it is \"$(OBJS_DIR)\"\ !
endif
	$(MAKE) -C $(LIBFT_DIR) clean
	cd $(MLX_DIR); ./configure clean

fclean: clean
ifneq ("$(BIN_DIR)",".")
	$(RM_DIR) $(BIN_DIR)
else
	@echo Refusing to delete/clear BIN_DIR as it is \"$(BIN_DIR)\"\ !
endif
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
#	$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
