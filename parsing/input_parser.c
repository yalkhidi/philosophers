/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:57:07 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/05 09:47:44 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	split_arg(char *arg, unsigned long *in_array, int *in_ptr)
{
	char	**splitted;
	int		j;
	int		in;

	j = 0;
	in = *in_ptr;
	splitted = ft_split(arg);
	while (splitted[j])
	{
		in_array[in] = ft_atoi(splitted[j]);
		if (!is_within_limits(in_array[in]))
			return (free_split(splitted), free(in_array), false);
		in++;
		j++;
	}
	*in_ptr = in;
	free_split(splitted);
	return (true);
}

unsigned long	*collect_input(int ac, char **av)
{
	unsigned long	*in_array;
	int				i;
	int				j;

	i = 1;
	j = 0;
	in_array = (unsigned long *)malloc(6 * sizeof(unsigned long));
	if (!in_array)
		return (NULL);
	if (!check_valid_chars(av) || !check_valid_operators(ac, av))
	{
		free(in_array);
		print_message("Error\n");
	}
	while (i < ac)
	{
		if (!split_arg(av[i], in_array, &j))
		{
			print_message("Error\n");
			return (NULL);
		}
		i++;
	}
	in_array[j] = 0;
	return (in_array);
}

t_input	*assign_inputs(unsigned long *input_array)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->n_philo = input_array[0];
	input->t_die = input_array[1];
	input->t_eat = input_array[2];
	input->t_sleep = input_array[3];
	if (input_array[4])
		input->n_t_philo_eat = input_array[4];
	else
		input->n_t_philo_eat = 0;
	input->finished = 0;
	input->dead = 0;
	free(input_array);
	return (input);
}
