/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zbakkas@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:56:33 by zbakkas           #+#    #+#             */
/*   Updated: 2024/05/09 20:45:21 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	print_bit(unsigned char bit, int pid)
{
	int	i;

	i = 128;
	while (i)
	{
		if (bit >= i)
		{
			bit -= i;
			if (kill(pid, SIGUSR1) == -1)
			{
				print_str("\033[0;31mCheck your PID ❌\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				print_str("\033[0;31mCheck your PID ❌\n");
				exit(1);
			}
		}
		i /= 2;
		usleep(120);
	}
}

void	print_len(int bit, int pid, int i)
{
	if (bit <= 0 && i == 32)
		return ;
	print_len(bit / 2, pid, ++i);
	if (bit % 2 == 0)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			print_str("\033[0;31mCheck your PID ❌\n");
			exit(1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			print_str("\033[0;31mCheck your PID ❌\n");
			exit(1);
		}
	}
	usleep(120);
}

void	send_str(char *str, int pid)
{
	int	x;
	int	i;

	i = 0;
	x = 0;
	while (str[x])
	{
		print_bit(str[x], pid);
		x++;
	}
}

void	handler(int signum)
{
	if (signum == SIGUSR1)
	{
		print_str("\033[0;32mMessage succesfully sent to the server ✅\n");
		exit(0);
	}
}

int	main(int arc, char **arv)
{
	int					i;
	struct sigaction	act;
	int					id;

	i = 0;
	if (arc != 3)
	{
		print_str("\033[0;31mUsage : ./client <pid> <message_to_send> ❌\n");
		return (0);
	}
	id = ft_atoi(arv[1]);
	if (id <= 2)
	{
		print_str("\033[0;31mCheck your PID ❌\n");
		exit(0);
	}
	act.sa_handler = handler;
	sigaction(SIGUSR1, &act, NULL);
	print_len(ft_strlen(arv[2]), id, i);
	send_str(arv[2], id);
	while (1)
		pause();
}
