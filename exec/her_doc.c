#include"../minishell.h"

char* open_random(void)
{
    static int i;
    char *name;

    i++;
    name = ft_strjoin("/tmp/", ft_itoa(i), -1);
    return (name);
}

int herenor(t_redir *red, int fd)
{
    char *str;
    while(1)
    {
        str = readline(">");
        if(!str || strcmp(str,red->file) == 0)
            break;
        ft_putstr_fd(expand_dollar(str, 1),fd);
        ft_putstr_fd("\n",fd);
    }
    return fd;
}
void open_herdoc(t_redir *red)
{
    int fd;
    char* name;

    name = open_random();
    fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    fd = herenor(red, fd);
    close(fd);
    fd = open(name, O_RDWR);
    if (fd == -1)
    {
        ft_putstr_fd("9ewed mn lbsala\n", 2);
        g_shell.ret = 1;
        g_shell.err = 1;
    }
    unlink(name);
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
            {
                open_herdoc(red);
            }
            red = red->next;
        }
        cmd = cmd->next;
    }
    dup2(fd,0);
}