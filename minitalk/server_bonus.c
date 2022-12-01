/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:14:00 by jinwoole          #+#    #+#             */
/*   Updated: 2022/06/23 22:14:17 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	pid_check(pid_t client_pid, siginfo_t *info)
{
	if (client_pid != info->si_pid)
		error_exit("signal interrupted");
}

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;
	client_pid = 0;
	if (!client_pid)
		client_pid = info->si_pid;
	pid_check(client_pid, info);
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			if (kill(client_pid, SIGUSR2) == -1)
				error_exit("signal failed");
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction; //sigaction구조체는 이렇게 정의되어 있다 핸들러,sigaction,samask,saflag등있다

	ft_putstr_fd("Server PID: ", 1); //서버 Pid출력
	ft_putnbr_fd(getpid(), 1); //서버pid출력
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = action; 
	s_sigaction.sa_flags = SA_SIGINFO; //siginfo플래그를 추가하면, sa_handler대신 3개의 인자를 받게되는 sa_sigaction
	//sigaction과 sighandler는 메모리가 중첩된다(하나만 사용할 수 있다)
	if (sigaction(SIGUSR1, &s_sigaction, 0) == -1)
		error_exit("signal failed");
	if (sigaction(SIGUSR2, &s_sigaction, 0) == -1)
		error_exit("signal failed");
	while (1)
		pause();
	return (0);
}
/*
	siginfo_t {
    	int      si_signo;  // 시그널 넘버
    	int      si_errno;  // errno 값
    	int      si_code;   // 시그널 코드
	    pid_t    si_pid;    // 프로세스 ID 보내기
    	uid_t    si_uid;    // 프로세스를 전송하는 실제 사용자 ID
    	int      si_status; // Exit 값 또는 시그널
    	clock_t  si_utime;  // 소모된 사용자 시간
    	clock_t  si_stime;  // 소모된 시스템 시간
    	sigval_t si_value;  // 시그널 값
    	int      si_int;    // POSIX.1b 시그널
    	void *   si_ptr;    // POSIX.1b 시그널
    	void *   si_addr;   // 실패를 초래한 메모리 위치
    	int      si_band;   // 밴드 이벤트
    	int      si_fd;     // 파일 기술자
}
*/	