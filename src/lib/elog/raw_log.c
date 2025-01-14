/**
 * @file log.c
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-04
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */
#include "elog.h"

/**
 * @brief 日志初始化
 *
 * @param lvl
 * @return int
 */
int raw_logInit(uint8_t lvl)
{
	/* 初始化日志系统 */
	elog_init();
	/* 开启文本颜色 */
	elog_set_text_color_enabled(true);
	/*  设置日志过滤器等级 */
	elog_set_filter_lvl(lvl);

	/* set EasyLogger log format */
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO & ~ELOG_FMT_DIR);
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_ALL & ~ELOG_FMT_DIR & ~ELOG_FMT_P_INFO);
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_ALL & ~ELOG_FMT_DIR & ~ELOG_FMT_P_INFO);
	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_ALL & ~ELOG_FMT_DIR & ~ELOG_FMT_P_INFO);
	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_DIR & ~ELOG_FMT_P_INFO);
	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_DIR & ~ELOG_FMT_P_INFO);

	/* 启动日志系统 */
	elog_start();
	/* 关闭缓冲区 */
	// elog_buf_enabled(false);
	/* 关闭异步输出 */
	// elog_async_enabled(false);
	return 0;
}