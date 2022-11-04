#include"../minishell.h"

char* open_random(void)
{
    static int i;
    char *name;

    i++;
    name = ft_strjoin("/tmp/", ft_itoa(i), -1);
    return (name);
}

void herenor(t_redir *red, int fd)
{
    char *str;
    while(1)
    {
        str = readline(">");
        if(!str || strcmp(str,red->file) == 0)
            break;
        ft_putstr_fd(str,fd);
        ft_putstr_fd("\n",fd);
    }
}
void open_herdoc(t_redir *red)
{
    int fd;
    char* name;

    name = open_random();
    fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    herenor(red, fd);
    close(fd);
    fd = open(name, O_RDONLY);
    red->fdin = fd;
}
void ft_here_doc(t_parse *cmd)
{
    t_redir *red;
    int fd;

    fd = dup(0);
    g_shell.here_sig = 27;
    while(cmd && cmd->error != 1)
    {
        red = cmd->redir;
        while(red && cmd->error != 1)
        {
            if(red->e_type == LESSANDLESS)
                open_herdoc(red);
            red = red->next;
        }
        cmd = cmd->next;
    }
    dup2(fd,0);
}