/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:51:24 by smodesto          #+#    #+#             */
/*   Updated: 2021/12/20 20:33:31 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define CLEAR "\033[H\033[J"
# include "hash_table.h"

//	parse
// flags [2: O_RDONLY |1: WRONLY CREAT APPEND| 0: WRONLY CREAT TRUNC ]
typedef struct s_file
{
	char				*path;
	int					flags;
	int					fd;
}						t_file;

typedef struct s_process
{
	char				*local_env[32];
	char				*command;
	char				*argv[64];
	t_file				*input_file[16];
	t_file				*output_file[16];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct s_job
{
	t_process			*process_lst;
	struct s_job		*next;
}						t_job;

typedef enum e_index
{
	I_ARGV,
	I_ENV,
	I_IRED,
	I_ORED,
	I_SIZE
}						t_index;

//env
typedef enum e_bool
{
	true,
	false
}					t_bool;

typedef struct s_variable
{
	char		*value;
	t_bool		env;
}				t_variable;

// token
typedef enum e_type
{
	T_UNDEFINED,
	T_WORD,
	T_IREDIRECT,
	T_OREDIRECT,
	T_OAPPEND,
	T_IREADNOHISTORY,
	T_BUILTIN
}					t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

// shell
typedef struct s_session
{
	t_ht_tab	*env;
	char		**envp;
	t_job		*jobs;
}	t_session;

typedef struct s_cmd_tab
{
	t_session	*session;
	char		*cmd_line;
	char		**cmd_splitted;
	char		*history;
	t_token		**piped_cmd;
	t_token		*simple_cmd;
}	t_cmd_tab;

#endif
