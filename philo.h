/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:36:59 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/09 19:45:07 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define NC	"\e[0m"
# define YELLOW	"\e[33m"
# define BYELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"


typedef struct s_philo
{
	int             id;
	int				philo_no;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;
	int				*dead;
	pthread_t		tid;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}   t_philo;


typedef struct s_program
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	int				dead;
	t_philo			*philo;
} t_program;


typedef struct s_args
{
	int             philo_no;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
}	t_args;



void	init_args(t_args *args, char *argv[]);
int		init_philo(t_program *program, t_args *args, int i);
int		init_program(t_program *program, t_args *args);

void    *thread_monitor();
void	*thread_routine(void	*arg);

int		ft_atoi(const char *str);


#endif //PHILO_H