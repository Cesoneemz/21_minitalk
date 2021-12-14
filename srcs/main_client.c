/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:00:17 by wlanette          #+#    #+#             */
/*   Updated: 2021/12/14 17:41:19 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	ft_print_error(char *message)
{
	if (message)
		free(message);
	ft_printf("%s\n", "[CLIENT]: Error while trying to send a message");
	exit(EXIT_FAILURE);
}

static int	ft_send_null(int pid, char *message)
{
	static int	counter = 0;

	if (counter++ != 8)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_print_error(message);
		return (0);
	}
	return (1);
}

static int	ft_send_message(int pid, char *str)
{
	static char		*message = NULL;
	static int		save_pid = 0;
	static int		bits = -1;

	if (str)
		message = ft_strdup(str);
	if (!message)
		ft_print_error(0);
	if (pid)
		save_pid = pid;
	if (message[++bits / 8])
	{
		if (message[bits / 8] & (0x80 >> (bits % 8)))
		{
			if (kill(save_pid, SIGUSR1) == -1)
				ft_print_error(message);
		}
		else if (kill(save_pid, SIGUSR2) == -1)
			ft_print_error(message);
		return (0);
	}
	if (!ft_send_null(save_pid, message))
		return (0);
	free(message);
	return (1);
}

static void	ft_router(int signum)
{
	int	end_signal;

	end_signal = 0;
	if (signum == SIGUSR1)
		end_signal = ft_send_message(0, 0);
	else if (signum == SIGUSR2)
		exit(EXIT_FAILURE);
	if (end_signal)
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_pid_validator(argv[1]))
	{
		ft_printf("%s\n", "[CLIENT]: Invalid arguments.");
		ft_printf("%s", "[CLIENT]: Arguments must be of the format: ");
		ft_printf("%s\n", "[./client <PID> <MESSAGE>]");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, ft_router);
	signal(SIGUSR2, ft_router);
	ft_send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
