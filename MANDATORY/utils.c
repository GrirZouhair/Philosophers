/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:19:11 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/05 11:21:35 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

static int	ft_long_number(long long result, char current_digit, int sign)
{
	if (result > 922337203685477580
		|| (result == 922337203685477580 && current_digit - '0' > 7))
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	int					i;
	int					sign;
	int long long		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-')
	{
		i++;
		sign = -1;
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
	return ((int)result * sign);
} 