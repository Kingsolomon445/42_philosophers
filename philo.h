/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:36:59 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/13 20:51:46 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"


typedef struct s_philo
{
	int             id;
	int				philo_no;
	int				meals_eaten;
	int				left_fork_acquired;
	int				right_fork_acquired;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				meals_to_eat;
	int				*dead;
	int				*philo_eaten;
	pthread_t		tid;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}   t_philo;


typedef struct s_program
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_t		monitor_tid;
	int				dead;
	int				philo_no;
	int				philo_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;
	t_philo			*philo;
} t_program;




void	init_args(t_program *program, char *argv[]);
int		init_philo(t_program *program, int i);
int		init_program(t_program *program);

void    *thread_monitor(void *arg);
void	*thread_routine(void *arg);

int		pick_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

int		ft_print_action(t_philo *philo, const char *action_str);
int		is_dead(t_philo *philo);
void	wait_for_all_threads(t_program *program);
void	destroy_all_mutex(t_program *program, int philo_no);
void	close_program(t_program *program);

size_t	get_time_in_ms();
int		ft_usleep(size_t ms);
void	ft_srand(int min_delay_ms, int max_delay_ms);

int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		check_if_all_positive(char **arg);
int		check_if_all_digits(char **arg);


#endif //PHILO_H