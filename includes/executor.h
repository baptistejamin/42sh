/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:24:26 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/15 19:40:15 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <parser.h>

void			launch_job(t_job *j, int foreground);
void			put_job_in_background(t_job *j);
void			put_job_in_foreground(t_job *j);
void			wait_for_job(t_job *j);
int				job_is_completed(t_job *j);

void			launch_process(t_process *p, int foreground);
void			update_process_status(t_job *j, pid_t pid, int status);

#endif