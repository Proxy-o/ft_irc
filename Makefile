

NAME = ircserv
FLAGS = -Wall -Wextra -Werror -I header -std=c++98 -fsanitize=address
CC = c++  
OBJ_DIR = obj
SRC_DIR = src
HEADER_DIR = header

all: $(NAME)

SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)

OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

HEADER = $(wildcard $(HEADER_DIR)/*.hpp)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $@




$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)



fclean: clean
	rm -f $(NAME)


re: fclean $(NAME)

.PHONY: all clean fclean re $(NAME)

