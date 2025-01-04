/**
 * @file main.c
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-04
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */
#include <stdio.h>
#include <unistd.h>
#include "log.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "main"
#endif

void _test_log(void)
{
	log_a("hello world");
	log_e("hello world");
	log_w("hello world");
	log_i("hello world");
	log_d("hello world");
	log_v("hello world");
}

int main(int argc, char* argv[])
{
	log_init(LOG_LVL_VERBOSE);

	_test_log();
	sleep(1);
	return 0;
}