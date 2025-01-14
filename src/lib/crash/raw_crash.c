/**
 * @file raw_crash.c
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-13
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */
#include <stdio.h>
#include <libunwind.h>

#include "raw_crash.h"
#include "raw_log.h"
#include "raw_log.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "crash"
#endif

/**
 * @brief 程序崩溃打印堆栈信息
 *
 */
void raw_crashPrintStack(void)
{
	unw_cursor_t  cursor;
	unw_context_t context;

	// Initialize cursor to current frame for local unwinding
	unw_getcontext(&context);
	unw_init_local(&cursor, &context);

	// Unwind frames one by one, going up the frame stack
	while (unw_step(&cursor) > 0) {
		unw_word_t offset, pc;
		unw_get_reg(&cursor, UNW_REG_IP, &pc);
		if (pc == 0) {
			break;
		}
		char sym[256];
		if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
			log_a("addr=0x%lx (%s+0x%lx)", (long)pc, sym, (long)offset);
		} else {
			log_a(" -- no symbol");
		}
	}
}
