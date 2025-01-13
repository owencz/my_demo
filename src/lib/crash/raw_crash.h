/**
 * @file raw_crash.h
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-13
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */

#ifndef _RAW_CRASH_H
#define _RAW_CRASH_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 程序崩溃打印堆栈信息
 *
 */
void raw_crashPrintStack(void);

#ifdef __cplusplus
}
#endif

#endif // _RAW_CRASH_H