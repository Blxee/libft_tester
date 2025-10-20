/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrum.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahiri- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 07:56:44 by atahiri-          #+#    #+#             */
/*   Updated: 2025/10/19 08:21:37 by atahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASTRUM_H
#define CASTRUM_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int g_test_failed;
char g_msg_buf[2048];
unsigned long g_buf_idx;
unsigned long g_test_i;
char *g_total_result[1024];
int g_total_len = 0;
int g_passed = 0;
int g_failed = 0;
int g_atexit_regitered = 0;

#define RUN_TEST(func) \
	if (!g_atexit_regitered) { \
		atexit(_test_summary); \
		g_atexit_regitered = 1; \
	} \
	g_test_failed = 0; \
	g_buf_idx = 0; \
	func(); \
	if (g_test_failed) { \
 		g_total_result[g_total_len++] = "\x1b[31;1mF\x1b[0m"; \
 		g_failed++; \
	} else { \
 		g_total_result[g_total_len++] = "\x1b[32;1mS\x1b[0m"; \
 		g_passed++; \
	} \
	if (g_test_failed) { \
		FAIL_MSG(func) \
		printf("%s", g_msg_buf); \
	} else \
		SUCCESS_MSG(func)

void _test_summary(void)
{
	for (int i = 0; i < g_total_len; i++)
		printf("%s", g_total_result[i]);
	printf("\n\t=> %d passed, %d failed\n", g_passed, g_failed);
}

#define PRINT_TYPE(exp) \
	_Generic((exp), \
		int:			sprintf(g_msg_buf + g_buf_idx, "%d", (int)(intptr_t)exp), \
		unsigned int:	sprintf(g_msg_buf + g_buf_idx, "%u", (unsigned int)(intptr_t)exp), \
		short:			sprintf(g_msg_buf + g_buf_idx, "%hd", (short)(intptr_t)exp), \
		unsigned short:	sprintf(g_msg_buf + g_buf_idx, "%hu", (unsigned short)(intptr_t)exp), \
		long:			sprintf(g_msg_buf + g_buf_idx, "%ld", (long)(intptr_t)exp), \
		unsigned long:	sprintf(g_msg_buf + g_buf_idx, "%lu", (unsigned long)exp), \
		char:			sprintf(g_msg_buf + g_buf_idx, "'%c'", (char)(intptr_t)exp), \
		unsigned char:	sprintf(g_msg_buf + g_buf_idx, "%hhx", (unsigned char)(intptr_t)exp), \
		float:			sprintf(g_msg_buf + g_buf_idx, "%.2f", (float)(intptr_t)exp), \
		double:			sprintf(g_msg_buf + g_buf_idx, "%.2f", (double)(intptr_t)exp), \
		long double:	sprintf(g_msg_buf + g_buf_idx, "%.2Lf", (long double)(intptr_t)exp), \
		char *:			sprintf(g_msg_buf + g_buf_idx, "\"%s\"", (char *)(intptr_t)exp), \
		default:		sprintf(g_msg_buf + g_buf_idx, "%p", (void *)(intptr_t)exp) \
	)

#define MAKE_PRINT_ARRAY(type) \
	void _test_print_array_##type(void *arr, unsigned long size) \
	{ \
		type *exp = (type *)arr; \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "{ "); \
		g_test_i = 0; \
		while (g_test_i < size) { \
			g_buf_idx += PRINT_TYPE((exp)[g_test_i]); \
			g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ", "); \
			g_test_i++; \
		} \
		if (size > 0 ) \
			g_buf_idx -= 2; \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, " }"); \
	} \

MAKE_PRINT_ARRAY(char)
MAKE_PRINT_ARRAY(int)
MAKE_PRINT_ARRAY(long)
MAKE_PRINT_ARRAY(uint8_t)
MAKE_PRINT_ARRAY(uint32_t)
MAKE_PRINT_ARRAY(uint64_t)

#define PRINT_ARRAY(exp, size) \
	_Generic((exp), \
			char *: _test_print_array_char(exp, size), \
			int *: _test_print_array_int(exp, size), \
			long *: _test_print_array_long(exp, size), \
			unsigned char *: _test_print_array_uint8_t(exp, size), \
			unsigned int *: _test_print_array_uint32_t(exp, size), \
			unsigned long *: _test_print_array_uint64_t(exp, size), \
			default: _test_print_array_long(exp, size) \
	)

#define TEST_INFO(info) \
	g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t\tinfo: %s = (", #info); \
	g_buf_idx += PRINT_TYPE(info); \
	g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \

#define SUCCESS_MSG(func) \
	printf("\x1b[42mSUCC\x1b[0m: %s\n", #func);

#define FAIL_MSG(func) \
	printf("\x1b[41mFAIL\x1b[0m: %s at line %d\n", #func, __LINE__);

#define ASSERT_TRUE(exp) \
	if (!exp) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #exp); \
		g_buf_idx += PRINT_TYPE(exp); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be true!\n"); \
		g_test_failed++; \
	}


#define ASSERT_FALSE(exp) \
	if (exp) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #exp); \
		g_buf_idx += PRINT_TYPE(exp); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be false!\n"); \
		g_test_failed++; \
	}

#define ASSERT_NULL(exp) \
	if (exp) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #exp); \
		g_buf_idx += PRINT_TYPE(exp); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be NULL!\n"); \
		g_test_failed++; \
	}

#define ASSERT_NON_NULL(exp) \
	if (!exp) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #exp); \
		g_buf_idx += PRINT_TYPE(exp); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to not be NULL!\n"); \
		g_test_failed++; \
	}

#define ASSERT_EQ(lhs, rhs) \
	if (lhs != rhs) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		g_buf_idx += PRINT_TYPE(lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to equal \x1b[1m%s\x1b[0m = (", #rhs); \
		g_buf_idx += PRINT_TYPE(rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_NE(lhs, rhs) \
	if (lhs == rhs) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		g_buf_idx += PRINT_TYPE(lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to not equal \x1b[1m%s\x1b[0m = (", #rhs); \
		g_buf_idx += PRINT_TYPE(rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_GT(lhs, rhs) \
	if (lhs <= rhs) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		g_buf_idx += PRINT_TYPE(lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be greater than \x1b[1m%s\x1b[0m = (", #rhs); \
		g_buf_idx += PRINT_TYPE(rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_GE(lhs, rhs) \
	if (lhs < rhs) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		g_buf_idx += PRINT_TYPE(lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be greater or equal to \x1b[1m%s\x1b[0m = (", #rhs); \
		g_buf_idx += PRINT_TYPE(rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_LT(lhs, rhs) \
	if (lhs >= rhs) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		g_buf_idx += PRINT_TYPE(lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be less than \x1b[1m%s\x1b[0m = (", #rhs); \
		g_buf_idx += PRINT_TYPE(rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_LE(lhs, rhs) \
	if (lhs > rhs) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		g_buf_idx += PRINT_TYPE(lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to be less or equal to \x1b[1m%s\x1b[0m = (", #rhs); \
		g_buf_idx += PRINT_TYPE(rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_ARR_EQ(lhs, rhs, size) \
	if (lhs == NULL || rhs == NULL || memcmp(lhs, rhs, size * sizeof(*lhs)) != 0) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		PRINT_ARRAY(lhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to equal \x1b[1m%s\x1b[0m = (", #rhs); \
		PRINT_ARRAY(rhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_ARR_NE(lhs, rhs, size) \
	if (lhs == NULL || rhs == NULL || memcmp(lhs, rhs, size * sizeof(*lhs)) == 0) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		PRINT_ARRAY(lhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to not equal \x1b[1m%s\x1b[0m = (", #rhs); \
		PRINT_ARRAY(rhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_STR_EQ(lhs, rhs) \
	if (!lhs || !rhs || strcmp(lhs, rhs) != 0) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = ", __FILE__, __LINE__, #lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\"%s\"", lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, " to equal \x1b[1m%s\x1b[0m: ", #rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\"%s\"", rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\n"); \
		g_test_failed++; \
	}

#define ASSERT_STR_NE(lhs, rhs) \
	if (!lhs || !rhs || strcmp(lhs, rhs) == 0) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = ", __FILE__, __LINE__, #lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\"%s\"", lhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, " to not equal \x1b[1m%s\x1b[0m: ", #rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\"%s\"", rhs); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\n"); \
		g_test_failed++; \
	}

#define ASSERT_MEM_EQ(lhs, rhs, size) \
	if (!lhs || !rhs || memcmp(lhs, rhs, size) != 0) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		PRINT_ARRAY((unsigned char *)lhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to equal \x1b[1m%s\x1b[0m = (", #rhs); \
		PRINT_ARRAY((unsigned char *)rhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#define ASSERT_MEM_NE(lhs, rhs, size) \
	if (!lhs || !rhs || memcmp(lhs, rhs, size) == 0) { \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, "\t%s:%d -> expected \x1b[1m%s\x1b[0m = (", __FILE__, __LINE__, #lhs); \
		PRINT_ARRAY((unsigned char *)lhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ") to equal \x1b[1m%s\x1b[0m = (", #rhs); \
		PRINT_ARRAY((unsigned char *)rhs, size); \
		g_buf_idx += sprintf(g_msg_buf + g_buf_idx, ")\n"); \
		g_test_failed++; \
	}

#endif
