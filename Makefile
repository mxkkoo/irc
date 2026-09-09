# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 17:51:25 by kyoussou          #+#    #+#              #
#    Updated: 2026/05/01 22:16:51 by kyoussou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CPP = c++
CFLAGS = -Wall -Werror -Wextra -Iincludes -std=c++98

SOURCES = main.cpp $(wildcard sources/*/*.cpp)
OBJECTS = $(addprefix objects/, $(patsubst %.cpp, %.o, $(SOURCES)))

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o $(NAME)

objects/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) -c $< -o $@

objects/sources/%.o: sources/%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) -c $< -o $@


objects/sources/utilities/%.o: sources/utilities/%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf objects

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
