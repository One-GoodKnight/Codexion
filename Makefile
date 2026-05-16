NAME			:= codexion
BUILD_DIR		:= .build

SRC_DIR			:= src
SRCS			:= 								\
	utils/ft_atoi.c								\
	utils/ft_get_time.c							\
	utils/ft_sleep.c							\
	utils/ft_printf.c							\
												\
	args.c										\
	main.c										\
	coder.c										\
	codexion.c									\
	dongle.c									\
	routine.c									\
	routine_cdr.c								\

INCLUDES		:= 								\
	include										\

SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
CPPFLAGS		:= $(addprefix -I,$(INCLUDES)) -MMD -MP
LDFLAGS 		:= -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
