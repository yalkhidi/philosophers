/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:07:29 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 14:27:45 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_input	t_input;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		eating;
	unsigned int		l_fork;
	unsigned int		r_fork;
	unsigned long		start_time;
	unsigned long		last_meal;
	unsigned int		meals_ate;
	pthread_mutex_t		meal_lock;
	t_input				*input;
}						t_philo;

typedef struct s_input
{
	unsigned int		n_philo;
	unsigned int		t_die;
	unsigned int		t_eat;
	unsigned int		t_sleep;
	unsigned int		n_t_philo_eat;
	unsigned int		dead;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		write_lock;
	unsigned int		*forks;
	pthread_mutex_t		*fork_locks;
	t_philo				*philos;
}						t_input;

int				words_count(char const *s);
char			**ft_split(char const *s);
void			free_split(char **split);
unsigned long	ft_atoi(const char *str);
bool			ft_isdigit(char d);
bool			is_within_limits(unsigned long num);
void			print_message(char *message);
bool			check_valid_chars(char **str);
bool			check_valid_operators(int ac, char **av);
unsigned int	*collect_input(int ac, char **av);
t_input			*assign_inputs(unsigned int *input_array);
void			init(t_input *input);
void			init_philos(t_input *input);
void			create_threads(t_input *input);
bool	still_alive(t_input *input);
void			*moniter(void *arg);
void			*routine(void *arg);
void			log_status(t_philo *philo, char *status);
void			smart_usleep(t_input *input, unsigned long time_in_ms);
unsigned long	get_time(void);
void			free_resources(t_input *input, char *message);
#endif