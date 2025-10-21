#include "libft/libft.h"

static char strmap_foo(unsigned int i, char c) { return c; }

static void striter_foo(unsigned int i, char *c) { }

static void lstiter_foo(void *p) { }

static void *lstmap_foo(void *p) { return NULL; }

int main(void)
{
	char str[64] = "hello\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

	ft_isalpha(' ');
	ft_isdigit(' ');
	ft_isalnum(' ');
	ft_isascii(' ');
	ft_isprint(' ');
	ft_strlen(str);
	ft_memset(str, ' ', 5);
	ft_bzero(str, 5);
	ft_memcpy(str, str, 5);
	ft_memmove(str, str, 5);
	ft_strlcpy(str, str, 5);
	ft_strlcat(str, str, 5);
	ft_toupper(' ');
	ft_tolower(' ');
	ft_strchr(str, ' ');
	ft_strrchr(str, ' ');
	ft_strncmp(str, str, 5);
	ft_memchr(str, ' ', 5);
	ft_memcmp(str, str, 5);
	ft_strnstr(str, str, 5);
	ft_atoi(str);
	free(ft_calloc(5, 5));
	free(ft_strdup(str));

	free(ft_substr(str, 0, 5));
	free(ft_strjoin(str, str));
	free(ft_strtrim(str, str));
	char **sp = ft_split(str, ' ');
	if (sp)
	{
		while (*sp)
			free((*sp)++);
		free(sp);
	}
	free(ft_itoa(9999));
	free(ft_strmapi(str, strmap_foo));
	ft_striteri(str, striter_foo);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd("", 1);
	ft_putendl_fd("", 1);
	ft_putnbr_fd(42, 1);

	t_list *lst = ft_lstnew(NULL);
	t_list *node = ft_lstnew(NULL);
	ft_lstadd_front(&lst, ft_lstnew(NULL));
	ft_lstadd_back(&lst, ft_lstnew(NULL));
	ft_lstadd_back(&lst, node);
	ft_lstsize(lst);
	ft_lstlast(lst);
	ft_lstiter(lst, lstiter_foo);
	t_list *mapped = ft_lstmap(lst, lstmap_foo, NULL);
	t_list *tmp = lst;
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	tmp->next = NULL;
	ft_lstdelone(node, NULL);
	ft_lstclear(&mapped, NULL);
	ft_lstclear(&lst, NULL);
}
