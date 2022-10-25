# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 12:57:40 by minkyeki          #+#    #+#              #
#    Updated: 2022/10/25 17:41:23 by minkyeki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------#
# NOTE: Change Directory name here
# ------------------------------------------------------#
SRC_DIR						= engine
LIBRARY_DIR					= ./library
LIBFT_DIR					= $(LIBRARY_DIR)/libft
# ------------------------------------------------------#
INC_DIR						= $(SRC_DIR)/include
INC_FLAG					= -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MINIRT_DIR)/include
# ENGINE-DIRECTORY
# ------------------------------------------------------ #
ENGINE_DIR					= $(SRC_DIR)/.

# (1) Core System Directory
# ------------------------------------------------------
ENGINE_CORE_DIR				= $(ENGINE_DIR)/gl_core
ENGINE_CORE_SRC				= engine input keyboard_handler mouse_handler

# (2) Graphics Library Directory
# ------------------------------------------------------ #
ENGINE_GL_DIR				= $(ENGINE_DIR)/gl_lib

#  NOTE:  Color library
	ENGINE_GL_COLOR_DIR			= $(ENGINE_GL_DIR)/color
	ENGINE_GL_COLOR_SRC			= gl_color_functions gl_color_get_functions

#  NOTE:  Math library
	ENGINE_GL_MATH_DIR			= $(ENGINE_GL_DIR)/math
	ENGINE_GL_MATH_SRC			=	matrix_4x4_multiply\
									matrix_4x4_rotate_functions\
									matrix_4x4_scale_functions\
									matrix_4x4_shear_functions\
									matrix_4x4_translate\
									matrix_projection_functions\
									matrix_util_functions\
									vector2 dvector2\
									vector3 dvector3\
									vector4 dvector4\

#  NOTE:  Draw-functions library
	ENGINE_GL_DRAW_DIR			= $(ENGINE_GL_DIR)/draw
	ENGINE_GL_DRAW_SRC			= gl_draw_pixel gl_draw_background gl_draw_line\
									gl_get_pixel_addr gl_get_pixel_color\


# (3) Dev-tools Directory (etc. Performance Checker)
# ------------------------------------------------------ #
ENGINE_ANALYSIS_DIR		= $(ENGINE_DIR)/gl_lib/time
ENGINE_ANALYSIS_SRC		= time

# (4) Engine Source
# ------------------------------------------------------ #
ENGINE_SRCS = $(addsuffix .c, $(addprefix $(ENGINE_CORE_DIR)/, $(ENGINE_CORE_SRC))) \
			  $(addsuffix .c, $(addprefix $(ENGINE_ANALYSIS_DIR)/, $(ENGINE_ANALYSIS_SRC))) \
			  $(addsuffix .c, $(addprefix $(ENGINE_GL_MATH_DIR)/, $(ENGINE_GL_MATH_SRC))) \
			  $(addsuffix .c, $(addprefix $(ENGINE_GL_COLOR_DIR)/, $(ENGINE_GL_COLOR_SRC))) \
			  $(addsuffix .c, $(addprefix $(ENGINE_GL_DRAW_DIR)/, $(ENGINE_GL_DRAW_SRC))) \


# MYAPP-DIRECTORY
MINIRT_DIR					= raytracer
MINIRT_SRC					= main helper\
							  update trace_ray\


MINIRT_OBJECTS_DIR		    = $(MINIRT_DIR)/objects
MINIRT_OBJECTS_SRC          = camera hit ray\
                              texture\
                              disk\
							  triangle square plane sphere cone cylinder\


MINIRT_PARSER_DIR		    = $(MINIRT_DIR)/parser
MINIRT_PARSER_SRC           = ft_atof ft_lscanf ft_lscanf_utils\
                              parse_rt_file_to_device


# MYAPP-SOURCE AL
MINIRT_SRCS  = $(addsuffix .c, $(addprefix $(MINIRT_DIR)/, $(MINIRT_SRC))) \
               $(addsuffix .c, $(addprefix $(MINIRT_PARSER_DIR)/, $(MINIRT_PARSER_SRC))) \
               $(addsuffix .c, $(addprefix $(MINIRT_OBJECTS_DIR)/, $(MINIRT_OBJECTS_SRC))) \

SRC = $(ENGINE_SRCS) $(MINIRT_SRCS)


# NOTE: Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


# NOTE: Makefile General
NAME			= minirt
CC				= cc
# CCFLAGS		= -Werror -Wextra -Wall
CCFLAGS			= -Werror -Wextra -Wall -g3 -fsanitize=address
RM				= rm -f

MLX_MACOS_COMPILE_FLAGS = -L$(LIBRARY_DIR)/mms -lmlx -framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore
MLX_LINUX_COMPILE_FLAGS = -L$(LIBRARY_DIR)/mlx -lmlx_Linux -L/usr/lib -I$(LIBRARY_DIR)/mlx -lXext -lX11 -lm -lz



OBJ = $(SRC:c=o)

all: $(NAME)

# NOTE: OS에 따라 자동 컴파일
# https://stackoverflow.com/questions/714100/os-detecting-makefile
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux) # LINUX
	LINUX = 1
	MLX_COMPILE_FLAGS = $(MLX_LINUX_COMPILE_FLAGS)
endif
ifeq ($(UNAME_S),Darwin) # MACOS
	OSX = 1
	MLX_COMPILE_FLAGS = $(MLX_MACOS_COMPILE_FLAGS)
endif


# NOTE: (OBJ)가 라이브러리보다 먼저 나와야 한다.
$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
ifdef LINUX
	@make -C $(LIBRARY_DIR)/mlx
	@$(CC) $(CCFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -lm $(MLX_COMPILE_FLAGS) -pthread -o $(NAME)
	@echo "$(BLUE)-------------------------------------------------$(DEF_COLOR)"
	@echo "$(BLUE)|                                               |$(DEF_COLOR)"
	@echo "$(BLUE)|   MiniRT Linux-X11 version compile finished.  |$(DEF_COLOR)"
	@echo "$(BLUE)|                                               |$(DEF_COLOR)"
	@echo "$(BLUE)-------------------------------------------------$(DEF_COLOR)"
endif
ifdef OSX
	@make -C $(LIBRARY_DIR)/mms
	@cp $(LIBRARY_DIR)/mms/libmlx.dylib .
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -lm $(MLX_COMPILE_FLAGS) -o $(NAME)
	@echo "$(BLUE)------------------------------------------------$(DEF_COLOR)"
	@echo "$(BLUE)|                                               |$(DEF_COLOR)"
	@echo "$(BLUE)|   MiniRt OSX-Metal version compile finished.  |$(DEF_COLOR)"
	@echo "$(BLUE)|                                               |$(DEF_COLOR)"
	@echo "$(BLUE)------------------------------------------------$(DEF_COLOR)"
endif


%.o: %.c
ifdef LINUX
	@$(CC) $(CCFLAGS) -I/usr/include -I$(LIBRARY_DIR)/mlx -O3 -c $< -o $@ $(INC_FLAG)
endif
ifdef OSX
	@$(CC) $(CCFLAGS) -I$(LIBRARY_DIR)/mms -c $< -o $@ $(INC_FLAG)
endif
	@echo "$(YELLOW)Compiling... \t$< $(DEF_COLOR)"






clean:
	@make fclean -C $(LIBFT_DIR)
	@$(RM) -f $(OBJ)
	@echo "$(BLUE)Minirt obj files has been deleted.$(DEF_COLOR)"

fclean:		clean
	@$(RM) -f $(NAME)
	@$(RM) -f libmlx.dylib
	@echo "$(BLUE)Minirt archive files has been deleted.$(DEF_COLOR)"

re:			fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything.$(DEF_COLOR)"

.PHONY:		all clean fclean re
