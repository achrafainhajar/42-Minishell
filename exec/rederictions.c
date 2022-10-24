#include"../minishell.h"

void input_red(t_redir *red)
{
    int input;
    if (access(red->file, F_OK) == -1)
	{
        exit(0);
	}
    else
    {
        input = open(red->file, O_RDONLY);
        dup2(input,0);
    }
    (void)red;
}

void output_red(t_redir *red)
{
    int output;
    
    output = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(output,1);
    (void)red;
}

void open_redir(t_parse *cmd,int *fd)
{

    close(fd[0]);
    if(cmd->redir)
    {
        if(cmd->redir->e_type == LESSANDLESS || cmd->redir->e_type == LESS)
        {
            input_red(cmd->redir);
        }
        else if(cmd->redir->e_type == GREATANDGREAT || cmd->redir->e_type == GREAT)
        {
            output_red(cmd->redir);
        }
    }
    else
        dup2(fd[1], 1);
}