/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 07:00:03 by recherra          #+#    #+#             */
/*   Updated: 2024/07/13 07:00:04 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef INIT_H
#define  INIT_H

#include "libft/libft.h"
#include <stdio.h> //printf, perror, strerror
#include <stdlib.h> //malloc, free, exit, getenv
#include <unistd.h> //write, close, fork, pipe, dup, dup2, ttyslot, ttyname, ttyslot, isatty, chdir, unlink, execve, read, getcwd
#include <fcntl.h> //open
#include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
#include <curses.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <termios.h> //tcgetattr, tcsetattr
#include <dirent.h> //closedir, readdir, opendir
#include <sys/stat.h> //stat, lstat
#include <sys/ioctl.h> //ioctl
#include <sys/wait.h> //wait, waitpid, wait3, wait4
#include <readline/readline.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
#include <readline/history.h>

#endif