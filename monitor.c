/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:00:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 11:20:54 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_starved(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if ((get_time() - philo->last_meal) >= philo->input->t_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	detect_death(t_input *input)
{
	int	i;

	i = -1;
	while (++i < (int)input->n_philo)
	{
		if (philo_starved(&input->philos[i]))
		{
			// smart_usleep(input, 10);
			log_status(&input->philos[i], "died");
			pthread_mutex_lock(&input->dead_lock);
			input->dead = 1;
			pthread_mutex_unlock(&input->dead_lock);
			return (1);
		}
	}
	return (0);
}

int	all_philos_full(t_input *input)
{
	int	i;
	int	finished_meals;

	if (input->n_t_philo_eat > 0)
	{
		i = -1;
		finished_meals = 0;
		while (++i < (int)input->n_philo)
		{
			pthread_mutex_lock(&input->philos[i].meal_lock);
			if (input->philos[i].meals_ate >= input->n_t_philo_eat)
				finished_meals++;
			pthread_mutex_unlock(&input->philos[i].meal_lock);
		}
		if (finished_meals == (int)input->n_philo)
		{
			pthread_mutex_lock(&input->dead_lock);
			input->dead = 1;
			pthread_mutex_unlock(&input->dead_lock);
			return (1);
		}
	}
	return (0);
}

void	*moniter(void *arg)
{
	t_input	*input;

	input = (t_input *)arg;
	while (1)
	{
		if (detect_death(input) || all_philos_full(input))
			break ;
	}
	return (arg);
}
