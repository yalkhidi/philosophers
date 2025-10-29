/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:54:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/09 15:34:46 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep_think(t_philo *philo)
{
	if (philo->input->n_philo != 1)
	{
		log_status(philo, "is sleeping");
		smart_usleep(philo->input, philo->input->t_sleep);
		log_status(philo, "is thinking");
		usleep(500);
	}
}

bool	check_greedy(t_philo *philo)
{
	bool	can_eat;

	pthread_mutex_lock(&philo->input->fork_locks[philo->l_fork]);
	pthread_mutex_lock(&philo->input->fork_locks[philo->r_fork]);
	if (philo->input->forks[philo->l_fork] == 0
		&& philo->input->forks[philo->r_fork] == 0)
		can_eat = true;
	else
		can_eat = false;
	pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
	pthread_mutex_unlock(&philo->input->fork_locks[philo->l_fork]);
	return (can_eat);
}

bool	lone_philo(t_philo *philo)
{
	if (philo->input->n_philo == 1)
	{
		pthread_mutex_lock(&philo->input->fork_locks[philo->r_fork]);
		log_status(philo, "has taken a fork");
		smart_usleep(philo->input, philo->input->t_die);
		pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
		return (true);
	}
	return (false);
}

void	philo_eat(t_philo *philo)
{
	if (lone_philo(philo))
		return ;
	while (!check_greedy(philo) && still_alive(philo->input))
		usleep(500);
	pthread_mutex_lock(&philo->input->fork_locks[philo->l_fork]);
	philo->input->forks[philo->l_fork] = 1;
	log_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->input->fork_locks[philo->r_fork]);
	philo->input->forks[philo->r_fork] = 1;
	log_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	log_status(philo, "is eating");
	smart_usleep(philo->input, philo->input->t_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_ate++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	philo->input->forks[philo->l_fork] = 0;
	philo->input->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&philo->input->fork_locks[philo->r_fork]);
	pthread_mutex_unlock(&philo->input->fork_locks[philo->l_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (still_alive(philo->input))
	{
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (arg);
}
