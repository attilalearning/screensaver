CC								=	cc
CFLAGS							=	-Wall -Wextra -Werror -g
VFLAGS							=	--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt
AR								=	ar rcs
RM								=	rm -f
RM_DIR							=	rm -rf
MK_QUIET						=	--no-print-directory

$(eval CURR_DIR					=	$(shell pwd))

BIN_DIR							=	./bin
NAME							=	$(BIN_DIR)/screensaver

LIB_DIR							= ./lib

LIBFT_DIR						=	$(LIB_DIR)/libft
LIBFT_A							=	$(LIBFT_DIR)/lib/libft.a

MLX_DIR							=	$(LIB_DIR)/mlx_linux
LIBMLX_A						=	$(MLX_DIR)/libmlx.a

SRCS_DIR						=	./srcs
SRCS_COLORS_DIR					=	$(SRCS_DIR)/colors
SRCS_CONTROLS_DIR				=	$(SRCS_DIR)/controls
SRCS_GRAPHICS_DIR				=	$(SRCS_DIR)/graphics
SRCS_RENDERERS_DIR				=	$(SRCS_DIR)/renderers
ALL_SRCS_DIRS					=	$(SRCS_DIR) \
									$(SRCS_COLORS_DIR) \
									$(SRCS_CONTROLS_DIR) \
									$(SRCS_GRAPHICS_DIR) \
									$(SRCS_RENDERERS_DIR)

OBJS_DIR						=	./obj

SRCS_FILES						=	\
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

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) \
		$(subst $(SRCS_DIR)/,$(OBJS_DIR)/,$(ALL_SRCS_DIRS))

$(LIBFT_A): FORCE
	@$(MAKE) $(MK_QUIET) SUBMOD=$(LIBFT_DIR) git_submodules
	@$(MAKE) $(MK_QUIET) -C $(LIBFT_DIR)

$(LIBMLX_A): FORCE
	@$(MAKE) $(MK_QUIET) SUBMOD=$(MLX_DIR) git_submodules
	@cd $(MLX_DIR); ./configure
	@$(MAKE) $(MK_QUIET) -C $(MLX_DIR)

git_submodules:
	@if [ ! -f $(SUBMOD)/Makefile ]; then \
		echo "[GIT]: Cloning $(SUBMOD)"; \
		git submodule update $(SUBMOD); \
		echo "[GIT]: Submodule $(SUBMOD) cloned."; \
	else \
		echo "[GIT]: Sub-module $(SUBMOD) is present."; \
	fi
#	git submodule update --init --recursive

FORCE:

valgrind:
	valgrind $(VFLAGS) ./$(NAME)

clean:
ifneq ("$(OBJS_DIR)",".")
	$(RM_DIR) $(OBJS_DIR)
else
	@echo Refusing to delete/clear OBJS_DIR as it is \"$(OBJS_DIR)\"\ !
endif
	if [ -d $(LIBFT_DIR) ]; then \
		$(MAKE) $(MK_QUIET) -C $(LIBFT_DIR) clean; \
	fi
	if [ -d $(MLX_DIR) ]; then \
		cd $(MLX_DIR); ./configure clean; \
	fi

fclean: clean
ifneq ("$(BIN_DIR)",".")
	$(RM_DIR) $(BIN_DIR)
else
	@echo Refusing to delete/clear BIN_DIR as it is \"$(BIN_DIR)\"\ !
endif
	$(RM) $(NAME)
	if [ -d $(LIBFT_DIR) ]; then \
		$(MAKE) $(MK_QUIET) -C $(LIBFT_DIR) fclean; \
	fi
#	$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all \
		clean \
		fclean \
		re \
		git_submodules \
		ensure_submod_repo_is_cloned hello
