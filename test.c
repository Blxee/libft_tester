#include "castrum.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include <bsd/string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

void test_ft_isalpha()
{
	ASSERT_TRUE(ft_isalpha('a'));
	ASSERT_TRUE(ft_isalpha('n'));
	ASSERT_TRUE(ft_isalpha('z'));
	ASSERT_TRUE(ft_isalpha('A'));
	ASSERT_TRUE(ft_isalpha('N'));
	ASSERT_TRUE(ft_isalpha('Z'));
	ASSERT_FALSE(ft_isalpha('0'));
	ASSERT_FALSE(ft_isalpha('\0'));
	ASSERT_FALSE(ft_isalpha('\n'));
	ASSERT_FALSE(ft_isalpha('!'));
	ASSERT_FALSE(ft_isalpha('@'));
}

void test_ft_isdigit()
{
	ASSERT_TRUE(ft_isdigit('0'));
	ASSERT_TRUE(ft_isdigit('5'));
	ASSERT_TRUE(ft_isdigit('9'));
	ASSERT_FALSE(ft_isdigit('a'));
	ASSERT_FALSE(ft_isdigit('$'));
	ASSERT_FALSE(ft_isdigit('*'));
	ASSERT_FALSE(ft_isdigit('Z'));
	ASSERT_FALSE(ft_isdigit('\0'));
	ASSERT_FALSE(ft_isdigit('\n'));
}

void test_ft_atoi(void)
{
	char *str;

	str = "12";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "0";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "-123";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "-0";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "abc";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "\t\t   123abc";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "-+123";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "+123";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "2147483647";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "-2147483648";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "-2147483649";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "2147483648";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "18434444444444444444444444444444444444444444444446744073709551616";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str = "-18434444444444444444444444444444444444444444444446744073709551616";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str =	"9223372036854775807";
	ASSERT_EQ(ft_atoi(str), atoi(str));

	str =	"-9223372036854775808";
	ASSERT_EQ(ft_atoi(str), atoi(str));
}

void test_ft_bzero(void)
{
	char mem[6];
	char target[6];

	memcpy(mem, "hello", 6);
	memcpy(target, "hello", 6);
	ft_bzero(mem, 6);
	bzero(target, 6);
	ASSERT_ARR_EQ(mem, target, 6);

	memcpy(mem, "hello", 6);
	memcpy(target, "hello", 6);
	ft_bzero(mem, 2);
	bzero(target, 2);
	ASSERT_ARR_EQ(mem, target, 6);

	memcpy(mem, "hello", 6);
	memcpy(target, "hello", 6);
	ft_bzero(mem, 0);
	bzero(target, (0));
	ASSERT_ARR_EQ(mem, target, 6);
}

void test_ft_calloc(void)
{
	void *ours = calloc(5, sizeof(char));
	void *theirs = ft_calloc(5, sizeof(char));
	ASSERT_ARR_EQ(ours, theirs, 5);
	free(ours);
	free(theirs);
}

void test_ft_isalnum(void)
{
	ASSERT_EQ(ft_isalnum('a'), isalnum('a'));
	ASSERT_EQ(ft_isalnum('Z'), isalnum('Z'));
	ASSERT_EQ(ft_isalnum('1'), isalnum('1'));
	ASSERT_EQ(ft_isalnum('%'), isalnum('%'));
	ASSERT_EQ(ft_isalnum('0'), isalnum('0'));
	ASSERT_EQ(ft_isalnum('9'), isalnum('9'));
	ASSERT_EQ(ft_isalnum('!'), isalnum('!'));
	ASSERT_EQ(ft_isalnum('\n'), isalnum('\n'));
	ASSERT_EQ(ft_isalnum('\0'), isalnum('\0'));
}

void test_ft_isascii(void)
{
	ASSERT_EQ(ft_isascii('a'), isascii('a'));
	ASSERT_EQ(ft_isascii('z'), isascii('z'));
	ASSERT_EQ(ft_isascii('\0'), isascii('\0'));
	ASSERT_EQ(ft_isascii(127), isascii(127));
	ASSERT_EQ(ft_isascii(128), isascii(128));
	ASSERT_EQ(ft_isascii(9999), isascii(9999));
	ASSERT_EQ(ft_isascii(-1), isascii(-1));
	ASSERT_EQ(ft_isascii(-128), isascii(-128));
	ASSERT_EQ(ft_isascii(-129), isascii(-129));
	ASSERT_EQ(ft_isascii(-9999), isascii(-9999));
}

void test_ft_isprint(void)
{
	char c;

	c = 'a';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 'z';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 'A';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 'Z';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = '0';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = '9';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = '$';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = '!';
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 32;
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 126;
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 127;
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 31;
	ASSERT_EQ(ft_isprint(c), isprint(c));

	c = 0;
	ASSERT_EQ(ft_isprint(c), isprint(c));
}

void test_ft_itoa(void)
{
	char *num;

	num = ft_itoa(123);
	ASSERT_STR_EQ(num, "123");
	free(num);

	num = ft_itoa(-123);
	ASSERT_STR_EQ(num, "-123");
	free(num);

	num = ft_itoa(1);
	ASSERT_STR_EQ(num, "1");
	free(num);

	num = ft_itoa(-1);
	ASSERT_STR_EQ(num, "-1");
	free(num);

	num = ft_itoa(0);
	ASSERT_STR_EQ(num, "0");
	free(num);

	num = ft_itoa(2147483647);
	ASSERT_STR_EQ(num, "2147483647");
	free(num);

	num = ft_itoa(-2147483648);
	ASSERT_STR_EQ(num, "-2147483648");
	free(num);
}

void test_ft_lstadd_back(void)
{
	char *content1 = "one";
	char *content2 = "two";
	char *content3 = "three";
	t_list *lst = NULL;
	t_list *next = ft_lstnew(content2);
	t_list *nextnext = ft_lstnew(content3);
	t_list target;

	ft_lstadd_back(&lst, ft_lstnew(content1));
	ft_lstadd_back(&lst, next);
	ft_lstadd_back(&lst, nextnext);

	target = (t_list){.content=content1, .next=next};
	ASSERT_MEM_EQ(lst, &target, sizeof(t_list));

	target = (t_list){.content=content2, .next=nextnext};
	ASSERT_MEM_EQ(lst->next, &target, sizeof(t_list));

	target = (t_list){.content=content3, .next=NULL};
	ASSERT_MEM_EQ(lst->next->next, &target, sizeof(t_list));

	ft_lstclear(&lst, NULL);
}

void test_ft_lstadd_front(void)
{
	char *content1 = "one";
	char *content2 = "two";
	char *content3 = "three";
	t_list *lst = NULL, *node1, *node2, *node3;
	t_list target;

	node1 = ft_lstnew(content1);
	ft_lstadd_front(&lst, node1);
	target = (t_list){.content=content1, .next=NULL};
	ASSERT_MEM_EQ(lst, &target, sizeof(t_list));

	node2 = ft_lstnew(content2);
	ft_lstadd_front(&lst, node2);
	target = (t_list){.content=content2, .next=node1};
	ASSERT_MEM_EQ(lst, &target, sizeof(t_list));
	target = (t_list){.content=content1, .next=NULL};
	ASSERT_MEM_EQ(lst->next, &target, sizeof(t_list));

	node3 = ft_lstnew(content3);
	ft_lstadd_front(&lst, node3);
	target = (t_list){.content=content3, .next=node2};
	ASSERT_MEM_EQ(lst, &target, sizeof(t_list));
	target = (t_list){.content=content2, .next=node1};
	ASSERT_MEM_EQ(lst->next, &target, sizeof(t_list));
	target = (t_list){.content=content1, .next=NULL};
	ASSERT_MEM_EQ(lst->next->next, &target, sizeof(t_list));

	ft_lstclear(&lst, NULL);
}

void _del_node(void *content)
{
	((char *)content)[0]++;
}

void test_ft_lstclear(void)
{
	char content1[] = "a";
	char content2[] = "b";
	char content3[] = "c";
	t_list *lst;
	
	// del is NULL
	lst = ft_lstnew(content1);
	ft_lstadd_front(&lst, ft_lstnew(content2));
	ft_lstadd_front(&lst, ft_lstnew(content3));

	ft_lstclear(&lst, NULL);

	ASSERT_NULL(lst);
	ASSERT_STR_EQ(content1, "a");
	ASSERT_STR_EQ(content2, "b");
	ASSERT_STR_EQ(content3, "c");

	// only list is null
	lst = NULL;
	ft_lstclear(&lst, _del_node);

	// both args are present
	lst = ft_lstnew(content1);
	ft_lstadd_front(&lst, ft_lstnew(content2));
	ft_lstadd_front(&lst, ft_lstnew(content3));

	ft_lstclear(&lst, _del_node);

	ASSERT_NULL(lst);
	ASSERT_STR_EQ(content1, "b");
	ASSERT_STR_EQ(content2, "c");
	ASSERT_STR_EQ(content3, "d");

	// both args are NULL
	lst = NULL;
	ft_lstclear(&lst, NULL);

}

void test_ft_lstdelone(void)
{
	char content[] = "A";
	t_list *lst = ft_lstnew(content);

	ft_lstdelone(lst, _del_node);
	ASSERT_STR_EQ(content, "B");

	lst = ft_lstnew(content);
	ft_lstdelone(lst, NULL);

	ft_lstdelone(NULL, _del_node);
}

void _iter_node(void *content) {
	if (content)
		((char *)content)[0]++;
}

void test_ft_lstiter(void)
{
	char content1[] = "a", content2[] = "b", content3[] = "c";
	t_list *lst = NULL;

	// test normal 3 node list with content
	ft_lstadd_front(&lst, ft_lstnew(content1));
	ft_lstadd_front(&lst, ft_lstnew(content2));
	ft_lstadd_front(&lst, ft_lstnew(content3));

	ft_lstiter(lst, _iter_node);

	ASSERT_STR_EQ(content1, "b");
	ASSERT_STR_EQ(content2, "c");
	ASSERT_STR_EQ(content3, "d");
	ft_lstclear(&lst, NULL);

	// test null first arg
	ft_lstiter(NULL, _iter_node);

	lst = ft_lstnew(NULL);

	// test null content
	ft_lstiter(lst, _iter_node);

	// test null second arg and null content
	ft_lstiter(lst, NULL);

	// test null second arg with content
	lst->content = content1;
	ft_lstiter(lst, NULL);

	ft_lstdelone(lst, NULL);
}

void test_ft_lstlast(void)
{
	t_list *lst = NULL;

	ASSERT_NULL(ft_lstlast(lst));

	ft_lstadd_back(&lst, ft_lstnew(NULL));
	ASSERT_EQ(ft_lstlast(lst), lst);

	ft_lstadd_back(&lst, ft_lstnew(NULL));
	ASSERT_EQ(ft_lstlast(lst), lst->next);

	ft_lstadd_back(&lst, ft_lstnew(NULL));
	ASSERT_EQ(ft_lstlast(lst), lst->next->next);

	ft_lstdelone(lst->next->next, NULL);
	lst->next->next = NULL;
	ASSERT_EQ(ft_lstlast(lst), lst->next);

	ft_lstclear(&lst, NULL);
}

void *_map_node(void *content)
{
	if (content == NULL)
		return (NULL);
	char *copy = strdup(content);
	copy[0]++;
	return (copy);
}

void _del_mapped_content(void *content)
{
	free(content);
}

void test_ft_lstmap(void)
{
	char content1[] = "a", content2[] = "b", content3[] = "c";
	t_list *lst = NULL, *result;

	ft_lstmap(NULL, _map_node, _del_mapped_content);

	// test normal 3 node list with content
	ft_lstadd_back(&lst, ft_lstnew(content1));
	ft_lstadd_back(&lst, ft_lstnew(content2));
	ft_lstadd_back(&lst, ft_lstnew(content3));

	result = ft_lstmap(lst, _map_node, _del_mapped_content);
	ft_lstclear(&lst, NULL);

	ASSERT_STR_EQ((char *)result->content, "b");
	ASSERT_STR_EQ((char *)result->next->content, "c");
	ASSERT_STR_EQ((char *)result->next->next->content, "d");
	ft_lstclear(&result, _del_mapped_content);

	// test null first arg
	ft_lstmap(NULL, _map_node, _del_mapped_content);

	lst = ft_lstnew(NULL);

	// test null content
	result = ft_lstmap(lst, _map_node, _del_mapped_content);
	ASSERT_NON_NULL(result);
	ASSERT_NULL(result->content);
	ft_lstdelone(result, _del_mapped_content);

	// test null second arg and null content
	result = ft_lstmap(lst, NULL, _del_mapped_content);
	ASSERT_NULL(result);

	// test null second arg with content
	lst->content = content1;
	result = ft_lstmap(lst, NULL, _del_mapped_content);
	ASSERT_NULL(result);

	ft_lstdelone(lst, NULL);
}

void test_ft_lstnew(void)
{
	char *content = "hello";
	t_list *lst, target;

	lst = ft_lstnew(content);
	target = (t_list){.content=content, .next=NULL};
	ASSERT_MEM_EQ(lst, &target, sizeof(t_list));
	ft_lstdelone(lst, NULL);

	lst = ft_lstnew(NULL);
	target = (t_list){.content=NULL, .next=NULL};
	ASSERT_MEM_EQ(lst, &target, sizeof(t_list));
	ft_lstdelone(lst, NULL);
}

void test_ft_lstsize(void)
{
	t_list *lst = ft_lstnew(NULL);

	ASSERT_EQ(ft_lstsize(NULL), 0);

	ASSERT_EQ(ft_lstsize(lst), 1);

	ft_lstadd_front(&lst, ft_lstnew(NULL));
	ASSERT_EQ(ft_lstsize(lst), 2);

	ft_lstadd_front(&lst, ft_lstnew(NULL));
	ASSERT_EQ(ft_lstsize(lst), 3);

	ft_lstclear(&lst, NULL);
}

void test_ft_memchr(void)
{
	ASSERT_EQ(ft_memchr("cbafgh", 'a', 6), memchr("cbafgh", 'a', 6));
	ASSERT_EQ(ft_memchr("cbafgh", 'z', 6), memchr("cbafgh", 'z', 6));
	ASSERT_EQ(ft_memchr("cbafgh", 'h', 3), memchr("cbafgh", 'h', 3));
	ASSERT_EQ(ft_memchr("cbafgh", 'f', 3), memchr("cbafgh", 'f', 3));
	ASSERT_EQ(ft_memchr("cbafgh", 'a', 3), memchr("cbafgh", 'a', 3));
	ASSERT_EQ(ft_memchr("cbafgh", 'a', 0), memchr("cbafgh", 'a', 0));
	ASSERT_EQ(ft_memchr(NULL, 'a', 0), memchr(NULL, 'a', 0));
}

void test_ft_memcmp(void)
{
	char *mem1, *mem2;
	size_t n;

	mem1 = "abc";
	mem2 = "abc";
	n = 3;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));

	mem1 = "abc";
	mem2 = "abcde";
	n = 3;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));

	mem1 = "abc";
	mem2 = "def";
	n = 3;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));

	mem1 = "abc";
	mem2 = "def";
	n = 0;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));

	mem1 = "abc";
	mem2 = "abc";
	n = 0;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));

	mem1 = "abc";
	mem2 = "abc";
	n = 9;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));

	mem1 = "abc";
	mem2 = "def";
	n = 9;
	ASSERT_EQ(ft_memcmp(mem1, mem2, n), memcmp(mem1, mem2, n));
}

void test_ft_memcpy(void)
{
	char *target;
	char mem1[32];
	char mem2[32];
	void *ret1;
	void *ret2;


	bzero(mem1, 32);
	bzero(mem2, 32);
	target = "hello";
	ret1 = ft_memcpy(mem1, target, 5);
	ASSERT_EQ(ret1, (void*)mem1);
	ret2 = memcpy(mem2, target, 5);
	ASSERT_EQ(ret2, (void*)mem2);
	ASSERT_STR_EQ(mem1, mem2);

	bzero(mem1, 32);
	bzero(mem2, 32);
	target = "hello";
	ret1 = ft_memcpy(mem1, target, 3);
	ASSERT_EQ(ret1, (void*)mem1);
	ret2 = memcpy(mem2, target, 3);
	ASSERT_EQ(ret2, (void*)mem2);
	ASSERT_STR_EQ(mem1, mem2);

	bzero(mem1, 32);
	bzero(mem2, 32);
	target = "hello";
	ret1 = ft_memcpy(mem1, target, 0);
	ASSERT_EQ(ret1, (void*)mem1);
	ret2 = memcpy(mem2, target, 0);
	ASSERT_EQ(ret2, (void*)mem2);
	ASSERT_STR_EQ(mem1, mem2);
}

void test_ft_memmove(void)
{
	char *target;
	char mem1[32];
	char mem2[32];
	void *ret1;
	void *ret2;


	bzero(mem1, 32);
	bzero(mem2, 32);
	target = "hello";
	ret1 = ft_memmove(mem1, target, 5);
	ASSERT_EQ(ret1, (void*)mem1);
	ret2 = memmove(mem2, target, 5);
	ASSERT_EQ(ret2, (void*)mem2);
	ASSERT_STR_EQ(mem1, mem2);

	bzero(mem1, 32);
	bzero(mem2, 32);
	target = "hello";
	ret1 = ft_memmove(mem1, target, 3);
	ASSERT_EQ(ret1, (void*)mem1);
	ret2 = memmove(mem2, target, 3);
	ASSERT_EQ(ret2, (void*)mem2);
	ASSERT_STR_EQ(mem1, mem2);

	bzero(mem1, 32);
	bzero(mem2, 32);
	target = "hello";
	ret1 = ft_memmove(mem1, target, 0);
	ASSERT_EQ(ret1, (void*)mem1);
	ret2 = memmove(mem2, target, 0);
	ASSERT_EQ(ret2, (void*)mem2);
	ASSERT_STR_EQ(mem1, mem2);
}

void test_ft_memset(void)
{
	char mem[6];
	char target[6];

	memcpy(mem, "hello", 6);
	memcpy(target, "hello", 6);
	ft_memset(mem, 'a', 6);
	memset(target, 'a', 6);
	ASSERT_ARR_EQ(mem, target, 6);

	memcpy(mem, "hello", 6);
	memcpy(target, "hello", 6);
	ft_memset(mem, 'a', 2);
	memset(target, 'a', 2);
	ASSERT_ARR_EQ(mem, target, 6);

	memcpy(mem, "hello", 6);
	memcpy(target, "hello", 6);
	ft_memset(mem, 9999, 0);
	memset(target, 9999, 0);
	ASSERT_ARR_EQ(mem, target, 6);
}

void test_ft_putchar_fd(void)
{
	char *file_name = "/tmp/_test_ft_putchar_fd.txt";
	int fd;
	int len;
	char buf[32];

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_putchar_fd('A', fd);
	close(fd);

	fd = open(file_name, O_RDONLY);
	len = read(fd, buf, 32);
	ASSERT_EQ(len, 1);
	ASSERT_EQ(buf[0], 'A');
	close(fd);
}

void test_ft_putendl_fd(void)
{
	char *file_name = "/tmp/_test_ft_putendl_fd.txt";
	int fd;
	int len;
	char buf[32];

	// test string = "hello"
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_putendl_fd("hello", fd);
	close(fd);

	bzero(buf, 32);
	fd = open(file_name, O_RDONLY);
	len = read(fd, buf, 32);
	ASSERT_EQ(len, 6);
	ASSERT_STR_EQ(buf, "hello\n");
	close(fd);

	// test empty string
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_putendl_fd("", fd);
	close(fd);

	bzero(buf, 32);
	fd = open(file_name, O_RDONLY);
	len = read(fd, buf, 32);
	ASSERT_EQ(len, 1);
	ASSERT_STR_EQ(buf, "\n");
	close(fd);
}

void test_ft_putnbr_fd(void)
{
	char *file_name = "/tmp/_test_ft_putnbr_fd.txt";
	int fd;
	int len;
	char buf[32];
	char *target;
	int nums[] = {123, -123, 0, 2147483647, -2147483648};

	for (int i = 0; i < sizeof(nums) / sizeof(*nums); i++)
	{
		target = ft_itoa(nums[i]);
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		ft_putnbr_fd(nums[i], fd);
		close(fd);

		bzero(buf, 32);
		fd = open(file_name, O_RDONLY);
		len = read(fd, buf, 32);
		ASSERT_EQ(len, strlen(target));
		ASSERT_STR_EQ(buf, target);
		close(fd);
		free(target);
	}
}

void test_ft_putstr_fd(void)
{
	char *file_name = "/tmp/_test_ft_putstr_fd.txt";
	int fd;
	int len;
	char buf[32];
	char *str;

	// test string = "hello"
	str = "hello";
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_putstr_fd(str, fd);
	close(fd);

	bzero(buf, 32);
	fd = open(file_name, O_RDONLY);
	len = read(fd, buf, 32);
	ASSERT_EQ(len, 5);
	ASSERT_STR_EQ(buf, str);
	close(fd);

	// test empty string
	str = "";
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_putstr_fd(str, fd);
	close(fd);

	bzero(buf, 32);
	fd = open(file_name, O_RDONLY);
	len = read(fd, buf, 32);
	ASSERT_EQ(len, 0);
	ASSERT_STR_EQ(buf, str);
	close(fd);
}

void test_ft_split(void)
{
	char *phrase;
	char **splt;
	int i;


	phrase = "   hello   w from     1337   ";
	char *target1[] = {"hello", "w", "from", "1337"};
	splt = ft_split(phrase, ' ');
	for (i = 0; i < sizeof(target1) / sizeof(*target1); i++)
		ASSERT_STR_EQ(splt[i], target1[i]);
	ASSERT_NULL((void *)splt[i]);
	for (i = 0; splt[i]; i++)
		free(splt[i]);
	free(splt);

	phrase = "   hello   ";
	char *target2[] = {"hello"};
	splt = ft_split(phrase, ' ');
	for (i = 0; i < sizeof(target2) / sizeof(*target2); i++)
		ASSERT_STR_EQ(splt[i], target2[i]);
	ASSERT_NULL((void *)splt[i]);
	for (i = 0; splt[i]; i++)
		free(splt[i]);
	free(splt);

	phrase = "";
	char *target3[] = {};
	splt = ft_split(phrase, ' ');
	ASSERT_NULL((void *)splt[i]);
	free(splt);

	phrase = "   hello";
	char *target4[] = {"hello"};
	splt = ft_split(phrase, ' ');
	for (i = 0; i < sizeof(target4) / sizeof(*target4); i++)
		ASSERT_STR_EQ(splt[i], target4[i]);
	ASSERT_NULL((void *)splt[i]);
	for (i = 0; splt[i]; i++)
		free(splt[i]);
	free(splt);

	phrase = "hello   ";
	char *target5[] = {"hello"};
	splt = ft_split(phrase, ' ');
	for (i = 0; i < sizeof(target5) / sizeof(*target5); i++)
		ASSERT_STR_EQ(splt[i], target5[i]);
	ASSERT_NULL((void *)splt[i]);
	for (i = 0; splt[i]; i++)
		free(splt[i]);
	free(splt);

	phrase = "    A   ";
	char *target6[] = {"A"};
	splt = ft_split(phrase, ' ');
	for (i = 0; i < sizeof(target6) / sizeof(*target6); i++)
		ASSERT_STR_EQ(splt[i], target6[i]);
	ASSERT_NULL((void *)splt[i]);
	for (i = 0; splt[i]; i++)
		free(splt[i]);
	free(splt);

	phrase = "A  B        C";
	char *target7[] = {"A", "B", "C"};
	splt = ft_split(phrase, ' ');
	for (i = 0; i < sizeof(target7) / sizeof(*target7); i++)
		ASSERT_STR_EQ(splt[i], target7[i]);
	ASSERT_NULL((void *)splt[i]);
	for (i = 0; splt[i]; i++)
		free(splt[i]);
	free(splt);

	ft_split(NULL, 0);
}

void test_ft_strchr(void)
{
	char *str;

	str = "hello";
	ASSERT_EQ(ft_strchr(str, 'h'), strchr(str, 'h'));

	str = "hello";
	ASSERT_EQ(ft_strchr(str, 'z'), strchr(str, 'z'));

	str = "hello";
	ASSERT_EQ(ft_strchr(str, 'o'), strchr(str, 'o'));

	str = "hello";
	ASSERT_EQ(ft_strchr(str, '\0'), strchr(str, '\0'));

	str = "";
	ASSERT_EQ(ft_strchr(str, '\0'), strchr(str, '\0'));

	str = "";
	ASSERT_EQ(ft_strchr(str, 'a'), strchr(str, 'a'));
}

void test_ft_strdup(void)
{
	char *target[] = {
		"hello",
		"",
		"hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello hello",
	};
	char *dup1;
	char *dup2;

	for (int i = 0; i < sizeof(target) / sizeof(*target); i++)
	{
		TEST_INFO(i);
		dup1 = ft_strdup(target[i]);
		dup2 = strdup(target[i]);
		ASSERT_STR_EQ(dup1, dup2);
		free(dup1);
		free(dup2);
	}
}

void _striteri_foo(unsigned int i, char *c)
{
	if (i & 1)
		*c = '0' + i;
}

void test_ft_striteri(void)
{
	char *str;

	str = strdup("hello");
	ft_striteri(str, &_striteri_foo);
	ASSERT_STR_EQ(str, "h1l3o");
	free(str);

	str = strdup("");
	ft_striteri(str, &_striteri_foo);
	ASSERT_STR_EQ(str, "");
	free(str);

}

void test_ft_strjoin(void)
{
	char *strs1[] =  {"he",    "hey", "",   "", "hello", NULL,    NULL};
	char *strs2[] =  {"llo",   "",    "hi", "", NULL,    "hello", NULL};
	char *target[] = {"hello", "hey", "hi", "", NULL,    NULL,    NULL};
	char *out;

	for (int i = 0; i < sizeof(strs1) / sizeof(*strs1); i++)
	{
		TEST_INFO(strs1[i]);
		TEST_INFO(strs2[i]);
		out = ft_strjoin(strs1[i], strs2[i]);
		if (target[i])
		{
			ASSERT_STR_EQ(out, target[i]);
		}
		else
		{
			ASSERT_NULL(out);
		}
		free(out);
	}
}

void test_ft_strlcat(void)
{
	char *dests[] =  {"world", "",      "world", "", "world", "world", "world", "world", "world", "world", "", "",    "", "world", "",      NULL};
	char *srcs[] =   {"hello", "hello", "",      "", "hello", "hello", "hello", "hello", "hello", "hello", "", "hey", "", "hello", "hello", "hey"};
	size_t sizes[] = {64,      64,      64,      64, 11,      10,      7,       5,       3,       0,       0,  0,     0,  3,       2,       0};
	char dest1[64];
	char dest2[64];

	for (int i = 0; i < sizeof(srcs) / sizeof(*srcs); i++)
	{
		if (dests[i])
		{
			strlcpy(dest1, dests[i], 64); // this is just for populating the dest1 buffer
			strlcpy(dest2, dests[i], 64); // this is just for populating the dest2 buffer
		}
		ASSERT_EQ(ft_strlcat(dest1, srcs[i], sizes[i]), strlcat(dest2, srcs[i], sizes[i]));
		ASSERT_STR_EQ(dest1, dest2);
	}
}

void test_ft_strlcpy(void)
{
	char *srcs[] =   {"hello", "hello", "",      "", "hello", "hello", "hello", "hello", "hello", "hello", "", "hey", ""};
	char *dests[] =  {"world", "",      "world", "", "world", "world", "world", "world", "world", "world", "", "",    ""};
	size_t sizes[] = {64,      64,      64,      64, 11,      10,      7,       5,       3,       0,       0,  0,     0};
	char dest1[64];
	char dest2[64];

	for (int i = 0; i < sizeof(srcs) / sizeof(*srcs); i++)
	{
		strlcpy(dest1, dests[i], 64); // this is just for populating the dest1 buffer
		strlcpy(dest2, dests[i], 64); // this is just for populating the dest2 buffer
		ASSERT_EQ(ft_strlcpy(dest1, srcs[i], sizes[i]), strlcpy(dest2, srcs[i], sizes[i]));
		ASSERT_STR_EQ(dest1, dest2);
	}
}

void test_ft_strlen(void)
{
	char *strs[] = {"hello", "", "\0", "\x1b"};

	for (int i = 0; i < sizeof(strs) / sizeof(*strs); i++)
	{
		ASSERT_EQ(ft_strlen(strs[i]), strlen(strs[i]));
	}
}

char _strmapi_foo(unsigned int i, char c)
{
	if (i & 1)
		return ('0' + i);
	else
		return (c);
}

void test_ft_strmapi(void)
{
	char *result;

	result = ft_strmapi("hello", &_strmapi_foo);
	ASSERT_STR_EQ(result, "h1l3o");
	free(result);

	result = ft_strmapi("", &_strmapi_foo);
	ASSERT_STR_EQ(result, "");
	free(result);
}

void test_ft_strncmp(void)
{
	char *strs1[] = {"abc", "abc", "abc", "abc", "abc", "abc", "abc", "abc", "abc", "ab",  "ab",  "ab",  "ab",  "ab",  "abc", "abc", "abc", "abc", "",    "",    "",    "",    "", ""};
	char *strs2[] = {"abc", "abc", "abc", "abc", "ab",  "ab",  "ab",  "ab",  "ab",  "abc", "abc", "abc", "abc", "abc", "",    "",    "",    "",    "abc", "abc", "abc", "abc", "", ""};
	size_t sizes[] = {3,    2,     4,     0,     2,     1,     3,     4,     0,     2,     1,     3,     4,     0,     3,     1,     4,     0,     3,     1,     4,     0,     3,  0};
	size_t n;
	int out;
	int expected;

	for (int i = 0; i < sizeof(strs1) / sizeof(*strs1); i++)
	{
		out = ft_strncmp(strs1[i], strs2[i], sizes[i]);
		expected = strncmp(strs1[i], strs2[i], sizes[i]);
		ASSERT_EQ(out, expected);
	}
}

void test_ft_strnstr(void)
{
	char *haystacks[] = {"hello", "hello", "hello", "hello", "hello", "hello", "hello",  "hello", "hello",  "hello", "hello", "hello", "hello", "hello", "hello", "hello",  "hello", "hello",  "hello", "hello", "hello", "hello", "hello", "hello",    "hello",  "hello", "hello",  "", "", "",    "",    "",    NULL,  NULL, NULL};
	char *needles[] =   {"he",    "hello", "llo",   "",      "zzz",   "zhel",  "helloz", "helz",  "zhello", "he",    "hello", "llo",   "",      "zzz",   "zhel",  "helloz", "helz",  "zhello", "he",    "hello", "llo",   "",      "zzz",   "zhel",     "helloz", "helz",  "zhello", "", "", "hey", "hey", "hey", "hey", "",   ""};
	size_t sizes[] =    {5,       5,       5,       5,       5,       5,       5,        5,       5,        3,       3,       3,       3,       3,       3,       3,        3,       3,        10,      10,      10,      10,      10,      10,         10,       10,      10,       0,  5,  0,     3,     5,     0,     5,    0};

	for (int i = 0; i < sizeof(haystacks) / sizeof(*haystacks); i++)
	{
		TEST_INFO(i);
		ASSERT_EQ(ft_strnstr(haystacks[i], needles[i], sizes[i]), strnstr(haystacks[i], needles[i], sizes[i]));
	}	
}

void test_ft_strrchr(void)
{
	char *str;

	str = "hello";
	ASSERT_EQ(ft_strrchr(str, 'l'), strrchr(str, 'l'));

	str = "hello";
	ASSERT_EQ(ft_strrchr(str, 'z'), strrchr(str, 'z'));

	str = "hello";
	ASSERT_EQ(ft_strrchr(str, 'o'), strrchr(str, 'o'));

	str = "hello";
	ASSERT_EQ(ft_strrchr(str, '\0'), strrchr(str, '\0'));

	str = "";
	ASSERT_EQ(ft_strrchr(str, '\0'), strrchr(str, '\0'));

	str = "";
	ASSERT_EQ(ft_strrchr(str, 'a'), strrchr(str, 'a'));
}

void test_ft_strtrim(void)
{
	char *str = "1234555h311o2343";
	char *target = "h311o";
	char *sep = "0123456789";
	char *out;

	out = ft_strtrim(str, sep);
	ASSERT_STR_EQ(out, target);
	free(out);

	str = "0123456789";
	target = "";
	out = ft_strtrim(str, sep);
	ASSERT_STR_EQ(out, target);
	free(out);
}

void test_ft_substr(void)
{
	char *strs[] = {         "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "", "", "", NULL, NULL, NULL, NULL};
	unsigned int starts[] = {0,       0,       0,       0,       2,       0,       4,       4,       0,  3,  3,  0,    0,    5,    10};
	size_t lengths[] = {     4,       5,       6,       10,      3,       0,       0,       10,      10, 2,  10, 5,    0,    0,    5};
	char *expected[] = {     "hell",  "hello", "hello", "hello", "llo",   "",      "",      "o",     "", "", "", NULL, NULL, NULL, NULL};
	char *result;

	for (int i = 0; i < sizeof(strs) / sizeof(*strs); i++)
	{
		TEST_INFO(strs[i]);
		TEST_INFO(starts[i]);
		TEST_INFO(lengths[i]);
		result = ft_substr(strs[i], starts[i], lengths[i]);
		if (expected[i])
		{
			ASSERT_STR_EQ(result, expected[i]);
		}
		else
		{
			ASSERT_NULL(result);
		}
		free(result);
	}
	result = ft_substr(NULL, 0, 5);
	ASSERT_NULL(result);
}

void test_ft_tolower(void)
{
	char c;

	c = 'A';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = 'Z';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = 'N';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = 'a';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = 'n';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = 'z';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = '1';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = '9';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = '\0';
	ASSERT_EQ(ft_tolower(c), tolower(c));

	c = '#';
	ASSERT_EQ(ft_tolower(c), tolower(c));
}

void test_ft_toupper(void)
{
	char c;

	c = 'A';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = 'Z';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = 'N';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = 'a';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = 'n';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = 'z';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = '1';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = '9';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = '\0';
	ASSERT_EQ(ft_toupper(c), toupper(c));

	c = '#';
	ASSERT_EQ(ft_toupper(c), toupper(c));
}


int main(void)
{
	RUN_TEST(test_ft_isalpha);
	RUN_TEST(test_ft_isdigit);
	RUN_TEST(test_ft_atoi);
	RUN_TEST(test_ft_bzero);
	RUN_TEST(test_ft_calloc);
	RUN_TEST(test_ft_isalnum);
	RUN_TEST(test_ft_isascii);
	RUN_TEST(test_ft_isprint);
	RUN_TEST(test_ft_itoa);
	RUN_TEST(test_ft_lstadd_back);
	RUN_TEST(test_ft_lstadd_front);
	RUN_TEST(test_ft_lstclear);
	RUN_TEST(test_ft_lstdelone);
	RUN_TEST(test_ft_lstiter);
	RUN_TEST(test_ft_lstlast);
	RUN_TEST(test_ft_lstmap);
	RUN_TEST(test_ft_lstnew);
	RUN_TEST(test_ft_lstsize);
	RUN_TEST(test_ft_memchr);
	RUN_TEST(test_ft_memcmp);
	RUN_TEST(test_ft_memcpy);
	RUN_TEST(test_ft_memmove);
	RUN_TEST(test_ft_memset);
	RUN_TEST(test_ft_putchar_fd);
	RUN_TEST(test_ft_putendl_fd);
	RUN_TEST(test_ft_putnbr_fd);
	RUN_TEST(test_ft_putstr_fd);
	RUN_TEST(test_ft_split);
	RUN_TEST(test_ft_strchr);
	RUN_TEST(test_ft_strdup);
	RUN_TEST(test_ft_striteri);
	RUN_TEST(test_ft_strjoin);
	RUN_TEST(test_ft_strlcat);
	RUN_TEST(test_ft_strlcpy);
	RUN_TEST(test_ft_strlen);
	RUN_TEST(test_ft_strmapi);
	RUN_TEST(test_ft_strncmp);
	RUN_TEST(test_ft_strnstr);
	RUN_TEST(test_ft_strrchr);
	RUN_TEST(test_ft_strtrim);
	RUN_TEST(test_ft_substr);
	RUN_TEST(test_ft_tolower);
	RUN_TEST(test_ft_toupper);
}
