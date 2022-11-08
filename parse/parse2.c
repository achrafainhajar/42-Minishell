
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

static int	ft_words(char const *s)
{
	int	i;
	int	cpt;
	int	j;
	// int	k;

	i = 0;
	cpt = 0;
	j = 1;
	// k = 0;
	while (s[i])
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
	return (cpt);
}

static int	ft_charcount(const char *s, int i)
{
	int	cnt;

	cnt = 0;
	while (s[i] && ft_is_space(s[i]))
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static char	**ft_splitcpy(const char *s, char **str, int wd)
{
	int	i;	
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] && wd > cnt)
	{
		j = 0;
		while (!ft_is_space(s[i]))
			i++;
		str[cnt] = f_malloc(sizeof(char ) * ft_charcount(s, i) + 1);
		if (!str[cnt])
			return (ft_freedom(str));
		while (ft_is_space(s[i]) && s[i])
		{
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
