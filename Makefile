NAME = ircserv
BONUS_NAME = bot
FLAGS = -Wall -Wextra -Werror -I header -std=c++98 
CC = c++  
OBJ_DIR = obj
SRC_DIR = src
HEADER_DIR = header
BONUS_DIR = bonus

all: $(NAME) $(BONUS_NAME)

SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp) 
BONUS_SRC = $(wildcard $(BONUS_DIR)/*.cpp)

OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
BONUS_OBJ = $(patsubst $(BONUS_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BONUS_SRC))

HEADER = $(wildcard $(HEADER_DIR)/*.hpp)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $@

$(BONUS_NAME): $(BONUS_OBJ) $(HEADER)
	$(CC) $(FLAGS) $(BONUS_OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.cpp $(HEADER)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
