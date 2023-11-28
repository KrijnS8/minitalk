/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 13:58:32 by kschelvi      #+#    #+#                 */
/*   Updated: 2023/11/28 17:44:52 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

volatile sig_atomic_t	g_received_request = false;

void	sigusr1_handler(int signum)
{
	(void)signum;
	g_received_request = true;
}

bool	validate_args(int argc, char *argv[])
{
	char	*str;

	if (argc != 3)
		return (false);
	str = argv[1];
	while (*str != '\0')
	{
		if (!ft_strchr("0123456789", *str))
			return (false);
		str++;
	}
	return (true);
}

void	send_bit(int bit, pid_t s_pid)
{
	if (bit == 0)
	{
		if (kill(s_pid, SIGUSR1) == -1)
			ft_putendl_fd("Error: unable to send signal", STDERR_FILENO);
	}
	else
	{
		if (kill(s_pid, SIGUSR2) == -1)
			ft_putendl_fd("Error: unable to send signal", STDERR_FILENO);
	}
}

void	send_msg(char *msg, pid_t s_pid)
{
	int		i;
	int		j;
	int		bit;

	i = 0;
	while (msg[i] != '\0')
	{
		j = 0;
		while (j < 8)
		{
			bit = (msg[i] >> j) & 1;
			send_bit(bit, s_pid);
			j++;
			while (!g_received_request)
				usleep(1);
			g_received_request = false;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	s_pid;

	if (!validate_args(argc, argv))
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	s_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, sigusr1_handler);
	send_msg(argv[2], s_pid);
	return (0);
}
