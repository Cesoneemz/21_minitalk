/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:40:35 by wlanette          #+#    #+#             */
/*   Updated: 2021/12/15 14:11:12 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_pid_validator(char *pid)
{
	if (!pid)
		return (0);
	if (ft_strlen(pid) > 5)
		return (0);
	while (*pid)
	{
		if (!ft_isdigit(*pid++))
			return (0);
	}
	return (1);
}
