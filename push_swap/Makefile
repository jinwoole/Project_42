CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME= push_swap
OPR_DIR	=	./operations/
FOND_DIR =	./foundation/
SRT_DIR =	./small_sort/
QIK_DIR =	./quick_sort/
UTL_DIR =	./utils/

SOURCES =	$(OPR_DIR)base_operations.c \
			$(OPR_DIR)basic_operations_sp.c \
			$(OPR_DIR)basic_operations_r.c \
			$(FOND_DIR)push_swap.c \
			$(FOND_DIR)sort.c \
			$(FOND_DIR)indexing.c \
			$(FOND_DIR)scan_error.c \
			$(SRT_DIR)five_sort.c \
			$(SRT_DIR)four_sort.c \
			$(SRT_DIR)two_three_sort.c \
			$(QIK_DIR)sort_quick_base.c \
			$(QIK_DIR)utils.c \
			$(UTL_DIR)ft_atoi.c \
			$(UTL_DIR)ft_lstnew.c \
			$(UTL_DIR)ft_lstsize.c \
			$(UTL_DIR)ft_lstlast.c \
			$(UTL_DIR)ft_lstadd_back.c \
			$(UTL_DIR)ft_lstsel.c \
			$(UTL_DIR)ft_lstfree.c \
			$(UTL_DIR)ft_lstadd.c \
			$(UTL_DIR)ft_lstdel.c \
			$(UTL_DIR)ft_putendl_fd.c \
			$(UTL_DIR)ft_putchar_fd.c \
			$(UTL_DIR)ft_putstr_fd.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o push_swap

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)
	$(RM) push_swap

re: fclean all

.PHONY: all clean fclean re