# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/09 14:23:52 by ofadahun          #+#    #+#              #
#    Updated: 2023/09/09 20:06:41 by ofadahun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO = philo

PHILO_SRCS_DIR = ./srcs
PHILO_OBJS_DIR = ./objs
PHILO_SRCS		=	$(wildcard $(PHILO_SRCS_DIR)/*.c)
PHILO_OBJS		=	$(addprefix $(PHILO_OBJS_DIR)/,$(notdir $(PHILO_SRCS:.c=.o)))

CC			=	cc
CFLAGS		=	-pthread -Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-rf

all:	$(PHILO)

$(PHILO_OBJS_DIR):
	mkdir -p $(PHILO_OBJS_DIR)
	
$(PHILO):	$(PHILO_OBJS_DIR) $(PHILO_OBJS)
	$(CC) -o $(PHILO) $(PHILO_OBJS)

$(PHILO_OBJS_DIR)/%.o:	$(PHILO_SRCS_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	$(RM) $(RMFLAGS) $(PHILO_OBJS_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(PHILO)

re: fclean all

.PHONY:	all clean fclean re