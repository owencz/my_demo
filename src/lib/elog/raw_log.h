/**
 * @file log.h
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-04
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */
#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "elog.h"

#define LOG_LVL_ASSERT	ELOG_LVL_ASSERT
#define LOG_LVL_ERROR	ELOG_LVL_ERROR
#define LOG_LVL_WARN	ELOG_LVL_WARN
#define LOG_LVL_INFO	ELOG_LVL_INFO
#define LOG_LVL_DEBUG	ELOG_LVL_DEBUG
#define LOG_LVL_VERBOSE ELOG_LVL_VERBOSE

/**
 * @brief 日志初始化
 *
 * @param lvl
 * @return int
 */
int raw_logInit(uint8_t lvl);

#ifdef __cplusplus
}
#endif
#endif
