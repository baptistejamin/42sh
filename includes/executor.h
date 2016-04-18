/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:24:26 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 12:10:55 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <libft.h>
# include <parser.h>
# include <signal.h>

void			exec_job_list(t_list *job_list);
void			prepare_job(t_job *j);
void			launch_job(t_job *j, int foreground);
void			put_job_in_background(t_job *j, int cont);
void			put_job_in_foreground(t_job *j, int cont);
void			wait_for_job(t_job *j);
int				job_is_completed(t_job *j);
int				job_is_stopped(t_job *j);

void			launch_process(t_process *p, pid_t pgid, int foreground);
void			launch_process_builtin(t_process *p);
int				update_process_status(t_job *j, pid_t pid, int status);
int				is_job_success(t_job *j);

#endif