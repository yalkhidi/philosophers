/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 09:59:29 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/09 15:26:14 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	still_alive(t_input *input)
{
	pthread_mutex_lock(&input->dead_lock);
	if (input->dead == 1)
	{
		pthread_mutex_unlock(&input->dead_lock);
		return (false);
	}
	pthread_mutex_unlock(&input->dead_lock);
	return (true);
}

void	log_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->input->write_lock);
	if (still_alive(philo->input))
		printf("%ld %u %s\n", get_time() - philo->start_time,
			philo->id, status);
	pthread_mutex_unlock(&philo->input->write_lock);
}

void	smart_usleep(t_input *input, unsigned long time_in_ms)
{
	unsigned long	start;

	start = get_time();
	while (still_alive(input))
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
