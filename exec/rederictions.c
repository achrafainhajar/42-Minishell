#include"../minishell.h"

int check_perm(struct stat fs,int r)
{
     if (fs.st_mode & r)
        return(0);
    return(1);
}
void input_red(t_redir *red)
{
    int input;

    if (access(red->file, F_OK) == -1)
	{
        ft_putstr_fd("minishell: no such file or directory: ", 2);
	    ft_putstr_fd(red->file, 2);
	    ft_putchar_fd('\n', 2);
        g_shell.ret = 1;
        g_shell.err = 1;
	}
    else if(access(red->file, R_OK)!= -1)
    {
        input = open(red->file, O_RDONLY);
        dup2(input,0);
    }
    else
    {
        ft_putstr_fd("minishell: permission denied: ", 2);
	    ft_putstr_fd(red->file, 2);
	    ft_putchar_fd('\n', 2);
        g_shell.ret = 1;
        g_shell.err = 1;
    }
}

void output_red1(t_redir *red)
{
    int output;
    
    output = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(access(red->file, W_OK)!= -1)
    {
        dup2(output,1);
        g_shell.ret = 0;
    }
    else
    {
        ft_putstr_fd("minishell: permission denied: ", 2);
	    ft_putstr_fd(red->file, 2);
	    ft_putchar_fd('\n', 2);
        g_shell.ret = 1;
        g_shell.err = 1;
    }
}
void output_red2(t_redir *red)
{
    int output;

    output = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if(access(red->file, W_OK)!= -1)
    {
        dup2(output,1);
        g_shell.ret = 0;
    }
    else
    {
        ft_putstr_fd("minishell: permission denied: ", 2);
	    ft_putstr_fd(red->file, 2);
	    ft_putchar_fd('\n', 2);
        g_shell.ret = 1;
        g_shell.err = 1;
    }
}
void open_redir(t_parse *cmd,int *fds,int *fd)
{
    (void)fds;
    if(cmd->next->cmd || cmd->next->redir)
    {
        dup2(fd[1], 1);
    }
    if(cmd->redir)
    {
        while(cmd->redir && !g_shell.err)
        {
            if(cmd->redir->e_type == LESSANDLESS || cmd->redir->e_type == LESS)
            {
                if(cmd->redir->e_type == LESS)
                    input_red(cmd->redir);
                else if (cmd->redir->e_type == LESSANDLESS)
                    dup2(cmd->redir->fdin, 0);
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
}