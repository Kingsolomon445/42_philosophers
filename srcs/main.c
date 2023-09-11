/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:22:40 by ofadahun          #+#    #+#             */
/*   Updated: 2023/09/10 15:55:12 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_for_all_threads(t_philo *philo, int philo_no)
{
	int			i;
	pthread_t	tid;
	
	i = 0;
	while (i < philo_no)
	{
		tid = (philo + i)->tid;
		pthread_join(tid, NULL);
		i++;
	}
}

void	destroy_all_mutex(t_program *program, int philo_no)
{
	int 	i;

	i = 0;
	pthread_mutex_destroy(&(program->write_lock));
	while (i < philo_no)
	{
		pthread_mutex_destroy(program->forks + i);
		i++;
	}
}


int main(int argc, char *argv[])
{
	t_philo     *philo;
	t_program   *program;
	t_args		*args;
	
	if (argc < 5)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat\
		 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	program = malloc(sizeof(t_program));
	if (!program)
		return (free(philo), 1);
	args = malloc(sizeof(t_args));
	if (!args)
		return (free(philo), free(program), 1);
	init_args(args, argv);
	init_program(program, args);
	wait_for_all_threads(program->philo, args->philo_no);
	destroy_all_mutex(program, args->philo_no);
	free(args);
	free(program->philo);
	free(program);
	return (0);
}
