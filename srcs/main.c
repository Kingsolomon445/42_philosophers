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


size_t    get_time_in_ms()
{
	struct timeval  current_time;
	size_t            ms;

	gettimeofday(&current_time, NULL);
	// printf("Time in seconds: %ld  && microseconds: %d\n", current_time.tv_sec, current_time.tv_usec);
	ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	// printf("Time in milliseconds: %ld\n", ms);
	return (ms);
}
void	wait_for_all_threads(t_philo *philo, int philo_no)
{
	int			i;
	pthread_t	tid;
	
	i = 0;
	while (i < philo_no)
	{
		tid = (philo + i)->tid;
		// printf("Main: Joined %d thread [%i]\n", i + 1, (philo + i)->id);
		pthread_join(tid, NULL);
		i++;
	}
}

void	destroy_all_mutex(t_program *program, int philo_no)
{
	int 	i;

	i = 0;
	pthread_mutex_destroy(&(program->death_lock));
	pthread_mutex_destroy(&(program->meal_lock));
	pthread_mutex_destroy(&(program->write_lock));
	while (i < philo_no)
	{
		pthread_mutex_destroy(program->forks + i);
		i++;
	}
}


int main(int argc, char *argv[])
{
	long        current_time;
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
	current_time = get_time_in_ms();
	init_args(args, argv);
	init_program(program, args);
	wait_for_all_threads(program->philo, args->philo_no);
	destroy_all_mutex(program, args->philo_no);
	free(args);
	free(program->philo);
	free(program);
	return (0);
}
