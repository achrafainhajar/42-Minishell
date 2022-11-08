
#include "../minishell.h"

static void	*ft_freedom(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

int    ft_is_space3(char c,int k)
{
    if (k == 1 && (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r'))
        return (0);
    return (1);
}

static int	ft_words(char const *s)
{
	int	i;
	int	cpt;
	int	j;

	i = 0;
	cpt = 0;
	j = 1;
	while (s[i])
	{
		if (s[i] == '\2')
		{
			while (s[i] != '\3')
			{
				if (!ft_is_space(s[i]))
					j = 1;
				else if (j == 1)
				{
					j = 0;
					cpt++;
				}
				i++;
			}
			if (s[i] == '\3' && !ft_is_space(s[i - 1]))
				cpt++;
		}
		i++;
	}
	return (cpt);
}

static int    ft_charcount(const char *s, int i,int k)
{
    int    cnt;

    cnt = 0;
    while (s[i] && ft_is_space3(s[i],k))
    {
        if(s[i] == '\2')
            k = 1;
        if(s[i] == '\3')
            k = 0;
        i++;
        cnt++;
    }
    return (cnt);
}

static char    **ft_splitcpy(const char *s, char **str, int wd)
{
    int    i;
    int    j;
    int    cnt;
    int k;
    k = 0;
    i = 0;
    cnt = 0;
    while (s[i] && wd > cnt)
    {
        j = 0;
        while (!ft_is_space3(s[i],k))
            i++;
        // if(s[i] == '\3')
        //     k = 0;
        str[cnt] = f_malloc(sizeof(char) * ft_charcount(s, i,k) + 1);
        if (!str[cnt])
            return (ft_freedom(str));
        while (ft_is_space3(s[i],k) && s[i])
        {
            if(s[i] == '\2')
                k=1;
            if(s[i] == '\3')
                k=0;
            str[cnt][j] = s[i];
            i++;
            j++;
        }
        str[cnt][j] = '\0';
        cnt++;
    }
    str[cnt] = NULL;
    return (str);
}

char	**ft_split2(char const *s)
{
	int		wd;
	char	**str;

	if (!s)
		return (0);
	wd = ft_words(s);
	str = f_malloc(sizeof(char *) * (wd + 1));
	if (str == NULL)
		return (0);
	return (ft_splitcpy(s, str, wd));
}
