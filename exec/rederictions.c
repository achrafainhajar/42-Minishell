#include"../minishell.h"

void input_red(t_redir *red)
{
    int input;
    if (access(red->file, F_OK) == -1)
	{
        ft_putstr_fd("minishell: no such file or directory: ", 2);
	    ft_putstr_fd(red->file, 2);
	    ft_putchar_fd('\n', 2);
        g_vars.exit_status = 1;
	}
    else
    {
        input = open(red->file, O_RDONLY);
        dup2(input,0);
    }
}

void output_red1(t_redir *red)
{
    int output;
    output = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(output,1);
}
void output_red2(t_redir *red)
{
    int output;

    output = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    dup2(output,1);
}
void open_redir(t_parse *cmd,int *fds,int *fd)
{

    if(cmd->redir)
    {
        while(cmd->redir)
        {
            if(cmd->redir->e_type == LESSANDLESS || cmd->redir->e_type == LESS)
            {
                if(cmd->redir->e_type == LESS)
                    input_red(cmd->redir);
                else
                {
                     dup2(cmd->redir->fdin, 0);
                }
            }
            else if(cmd->redir->e_type == GREATANDGREAT || cmd->redir->e_type == GREAT)
            {
                if(cmd->redir->e_type == GREAT)
                     output_red1(cmd->redir);
                else
                    output_red2(cmd->redir);
            }
            cmd->redir = cmd->redir->next;
        }
    }
    else if(cmd->next->cmd)
        dup2(fd[1], 1);
    else
         dup2(fds[1], 1);
}