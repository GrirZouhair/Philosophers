/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:19:11 by zogrir            #+#    #+#             */
/*   Updated: 2025/06/12 14:51:57 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_long_number(long result, char current_digit, int sign)
{
	if (result > 214748364 || (result == 214748364 && current_digit - '0' > 7))
	{
		if (sign == 1)
			return (-1);
		if (current_digit - '0' > 8)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		if (ft_long_number(result, s[i], sign) != 1)
			return (ft_long_number(result, s[i], sign));
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

int	ft_zero_check(t_philo *philo)
{
	if (philo->time_to_die == 0
		|| philo->time_to_eat == 0
		|| philo->time_to_sleep == 0)
		return (error_msg_caller(3), 0);
	if (philo->max_meals == 0)
		return (error_msg_caller(3), 0);
	return (1);
}

int	ft_overflow_check(t_philo *philo)
{
	if (philo->num_philos == -1
		|| philo->time_to_die == -1
		|| philo->time_to_eat == -1
		|| philo->time_to_sleep == -1)
		return (error_msg_caller(4), 0);
	if (philo->max_meals == -1)
		return (error_msg_caller(4), 0);
	return (1);
}
