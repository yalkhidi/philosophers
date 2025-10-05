/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:57:34 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/01 09:26:20 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	check_valid_chars(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(ft_isdigit(str[i][j])) &&
			str[i][j] != '+' && str[i][j] != ' ')
				return (false);
			else if (str[i][j] == '+' )
			{
				if ((j > 0 && str[i][j - 1] != ' ') ||
				!ft_isdigit(str[i][j + 1]))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_valid_token(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '+' ) && str[1] == '\0')
		return (false);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '\0')
		return (false);
	else if (str[i])
	{
		while (str[i])
		{
			if ((str[i] == '+') && !ft_isdigit(str[i + 1]))
				return (false);
			i++;
		}
	}
	return (true);
}

bool	check_valid_operators(int ac, char **av)
{
	int	i;
	int	count;

	i = ac - 1;
	count = 0;
	while (i > 0)
	{
		if (!is_valid_token(av[i]) || count > 5)
			return (false);
		count += words_count(av[i]);
		i--;
	}
	if (count < 4 || count > 5)
		return (false);
	return (true);
}
