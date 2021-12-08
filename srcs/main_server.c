/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:25:35 by wlanette          #+#    #+#             */
/*   Updated: 2021/12/08 14:06:51 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static char	*ft_add_char_to_str(char *str, char c)
{
	char	*s_str;
	char	*result;
	char	*tmp;

	result = (char *)malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	s_str = str;
	if (!s_str)
	{
		s_str = (char *)malloc(sizeof(char));
		if (!s_str)
			return (NULL);
		s_str[0] = '\0';
	}
	result[0] = c;
	result[1] = '\0';
	tmp = result;
	result = ft_strjoin(s_str, result);
	free(tmp);
	free(s_str);
	return (result);
}

static char	ft_print_error(int pid, char *message)
{
	if (message)
		free(message);
	ft_printf("[SERVER]: Error while trying to send a signal");
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

static char	*ft_print_message(char *message)
{
	ft_printf("%s\n", message);
	free(message);
	return (NULL);
}

static void	ft_handler(int signum, siginfo_t *info, void *context)
{
	static char		c = 0xFF;
	static int		bits = 0;
	static char		*message = NULL;

	(void)context;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c)
			message = ft_add_char_to_str(message, c);
		else
			message = ft_print_message(message);
		bits = 0;
		c = 0xFF;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_print_error(info->si_pid, message);
}

int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			sa_block;

	sigemptyset(&sa_block);
	sigaddset(&sa_block, SIGINT);
	sigaddset(&sa_block, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = sa_block;
	sa_signal.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	ft_printf("PID: %i\n", getpid());
	while (1)
		pause();
}
