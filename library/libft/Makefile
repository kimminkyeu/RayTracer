# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 15:31:26 by minkyeki          #+#    #+#              #
#    Updated: 2022/10/26 12:30:19 by minkyeki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = libft.a
CC              = cc
CFLAGS          = -Wall -Wextra -Werror
INCLUDE         = include
RM              = rm -f
AR              = ar rcs

# NOTE : Add Source directory here
# ------------------------------------------------------ #
SRC_DIR         = src
LIBC_DIR        = $(SRC_DIR)/LibC
GNL_DIR         = $(SRC_DIR)/Get_next_line
PRINF_DIR       = $(SRC_DIR)/Printf
STRING_DIR      = $(SRC_DIR)/String

VECTOR_DIR      = $(SRC_DIR)/Vector
VECTOR_VOID_DIR      = $(VECTOR_DIR)/vector_void
VECTOR_UCHAR_DIR     = $(VECTOR_DIR)/vector_unsigned_char

# NOTE : Add Source files here
# ------------------------------------------------------ #
LIBC_SRC        = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha \
				  ft_isascii ft_isdigit ft_isprint ft_itoa ft_memchr \
				  ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd \
				  ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr \
				  ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy \
				  ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr \
				  ft_strtrim ft_substr ft_tolower ft_toupper \
				  ft_isspace ft_nbrlen ft_putnbr_uint_fd ft_nbrlen_uint \
				  ft_convert_nbr_base_malloc ft_nputstr_fd ft_atoi_base \
				  ft_strjoin_all ft_isinteger \
				  ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
				  ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

GNL_SRC         = get_next_line get_next_line_utils \
				  get_next_line_bonus get_next_line_utils_bonus

PRINTF_SRC      = ft_printf ft_printf_hex ft_printf_info ft_printf_parse \
				  ft_printf_spec1 ft_printf_spec2

STRING_SRC      = string_create string_modify string_modify2 string_utils

# VECTOR_SRC      = vector_create vector_modify vector_iterate vector
VECTOR_VOID_SRC      = vector_create vector_create2 vector_modify vector_iterate

# NOTE : Add to SRC here
# ------------------------------------------------------ #
SRC = $(addsuffix .c, $(addprefix $(LIBC_DIR)/,   $(LIBC_SRC)))        \
	  $(addsuffix .c, $(addprefix $(GNL_DIR)/,    $(GNL_SRC)))         \
	  $(addsuffix .c, $(addprefix $(PRINF_DIR)/,  $(PRINTF_SRC)))      \
	  $(addsuffix .c, $(addprefix $(STRING_DIR)/, $(STRING_SRC)))      \
	  $(addsuffix .c, $(addprefix $(VECTOR_VOID_DIR)/, $(VECTOR_VOID_SRC))) \
# ------------------------------------------------------ #

OBJ = $(SRC:c=o)


# Colors
DEF_COLOR       = \033[0;39m
GRAY            = \033[0;90m
RED             = \033[0;91m
GREEN           = \033[0;92m
YELLOW          = \033[0;93m
BLUE            = \033[0;94m
MAGENTA         = \033[0;95m
CYAN            = \033[0;96m
WHITE           = \033[0;97m


# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $^
	@echo "$(GREEN)---------------------------$(DEF_COLOR)"
	@echo "$(GREEN)|                         |$(DEF_COLOR)"
	@echo "$(GREEN)| Libft compile finished. |$(DEF_COLOR)"
	@echo "$(GREEN)|                         |$(DEF_COLOR)"
	@echo "$(GREEN)---------------------------$(DEF_COLOR)"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(GREEN)Compiling... \t$< $(DEF_COLOR)"

clean:
	@rm -rf $(OBJ)
	@echo "$(CYAN)Libft obj files has been deleted.$(DEF_COLOR)"

fclean: clean
	@${RM} ${NAME}
	@echo "$(CYAN)Libft archive files has been deleted.$(DEF_COLOR)"

re: fclean all
	@echo "$(BLUE)Cleaned and rebuilt everything.$(DEF_COLOR)"

.PHONY: all clean fclean re bonus
