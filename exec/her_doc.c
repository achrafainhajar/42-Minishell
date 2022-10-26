#include"../minishell.h"
void herenor(t_redir *red)
{
    char *str;
    while(1)
    {
        str = readline(">");
        if(strcmp(str,red->file) == 0)
            break;
        ft_putstr_fd(str,red->fdout);
        ft_putstr_fd("\n",red->fdout);
    }
    exit(0);
}
void open_herdoc(t_redir *red)
{
    int fd[2];
    pid_t pid;
    pipe(fd);
    red->fdin = fd[0];
    red->fdout = fd[1];
    pid = fork();
    if(pid == 0)
    {
        close(fd[0]);
        herenor(red);
    }
    close(fd[1]);
    while(wait(NULL) > 0);
}
void ft_here_doc(t_parse *cmd)
{
    t_redir *red;
    while(cmd)
    {
        red = cmd->redir;
        while(red)
        {
            if(red->e_type == LESSANDLESS)
                open_herdoc(red);
            red = red->next;
        }
        cmd = cmd->next;
    }
}