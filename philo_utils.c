/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 09:59:29 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 14:34:15 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->input->write_lock);
	pthread_mutex_lock(&philo->input->dead_lock);
	if (philo->input->dead != 1)
		printf("%ld %u %s\n", get_time() - philo->start_time,
			philo->id, status);
	pthread_mutex_unlock(&philo->input->dead_lock);
	pthread_mutex_unlock(&philo->input->write_lock);
}

void	smart_usleep(t_input *input, unsigned long time_in_ms)
{
	unsigned long	start;

	start = get_time();
	while (!input->dead)
	{
		if ((get_time() - start) >= time_in_ms)
			break ;
		usleep(500);
	}
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_in_ms);
}

void	free_resources(t_input *input, char *message)
{
	unsigned int	i;

	if (input->forks)
	{
		i = -1;
		while (++i < input->n_philo)
			pthread_mutex_destroy(&input->forks[i]);
		free(input->forks);
	}
	if (input->philos)
	{
		i = -1;
		while (++i < input->n_philo)
			pthread_mutex_destroy(&input->philos[i].meal_lock);
		free(input->philos);
	}
	if (input)
	{
		pthread_mutex_destroy(&input->write_lock);
		pthread_mutex_destroy(&input->dead_lock);
		free(input);
	}
	if (message)
		print_message(message);
}
