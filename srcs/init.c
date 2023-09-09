/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:25:41 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/09 20:01:10 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_args(t_args *args, char *argv[])
{
	int	i;

	i = 1;
	while(argv[i])
	{
		if (i == 1)
			args->philo_no = ft_atoi(argv[i]);
		if (i == 2)
			args->time_to_die = ft_atoi(argv[i]);
		if (i == 3)
			args->time_to_eat = ft_atoi(argv[i]);
		if (i == 4)
			args->time_to_sleep = ft_atoi(argv[i]);
		if (i == 5)
			args->meals_to_eat = ft_atoi(argv[i]);
		i++;
	}
}

int	init_philo(t_program *program, t_args *args, int i)
{
	t_philo	*philo;

	philo = program->philo + i;
	philo->id = i + 1;
	philo->philo_no = args->philo_no;
	philo->time_to_die = args->time_to_die;
	philo->time_to_eat = args->time_to_eat;
	philo->time_to_sleep = args->time_to_sleep;
	philo->meals_to_eat = args->meals_to_eat;
	philo->dead = &program->dead;
	philo->death_lock = &program->death_lock;
	philo->meal_lock = &program->meal_lock;
	philo->write_lock = &program->write_lock;
	philo->l_fork = program->forks + i;
	if (i == args->philo_no - 1)
		philo->r_fork = program->forks;
	else
		philo->r_fork = program->forks + i + 1;
	pthread_create(&philo->tid, NULL, thread_routine, philo);
	return (1);
}

pthread_mutex_t	*init_forks(int philo_no)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * philo_no);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < philo_no)
	{
		pthread_mutex_init(forks + i, NULL);
		i++;
	}
	return (forks);
}

int	init_program(t_program *program, t_args *args)
{
	int	i;

	i = 0;
	program->dead = 0;
	program->philo = (t_philo *)malloc(sizeof(t_philo) * (args->philo_no));
	if (!program->philo)
		return (0);
	pthread_mutex_init(&program->death_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	program->forks = init_forks(args->philo_no);
	while(i < args->philo_no)
	{
		init_philo(program, args, i);
		i++;
	}
	return (1);
}