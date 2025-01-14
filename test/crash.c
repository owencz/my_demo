/**
 * @file crash.c
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-13
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <raw_log.h>
#include <signal.h>
#include "raw_crash.h"

/**
 * @brief  崩溃回调
 *
 * @param sig
 */
static void crash_handler(int sig)
{
	log_a("=======    crash stack sig=[%d]    =======", sig);
	raw_crashPrintStack();
}

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char* argv[])
{
	raw_logInit(LOG_LVL_DEBUG);

	signal(SIGSEGV, crash_handler);
	signal(SIGABRT, crash_handler);
	signal(SIGBUS, crash_handler);
	signal(SIGFPE, crash_handler);
	signal(SIGILL, crash_handler);
	signal(SIGINT, crash_handler);
	signal(SIGTERM, crash_handler);

	int64_t i = 0;

	while (1) {
		i++;
		sleep(1);
		log_i("i = %lld", i);
	}
	return 0;
}