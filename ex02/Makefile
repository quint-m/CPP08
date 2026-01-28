NAME		= mutantstack

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD -MP

SRCDIR		= src
OBJDIR		= obj

SOURCES		= $(SRCDIR)/main.cpp

OBJECTS		= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPS		= $(OBJECTS:.o=.d)

GREEN		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
NC			= \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "$(YELLOW)Linking $(NAME)...$(NC)\n"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(GREEN)$(NAME) created successfully!$(NC)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@printf "$(YELLOW)Compiling $<...$(NC)\r"
	@$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	@printf "$(RED)Removing object files...$(NC)\n"
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "$(RED)Removing $(NAME)...$(NC)\n"
	@rm -f $(NAME)

re: fclean all

# Declare phony targets
.PHONY: all clean fclean re

-include $(DEPS)
