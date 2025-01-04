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
int log_init(uint8_t lvl)
{
	/* 初始化日志系统 */
	elog_init();
	/* 开启文本颜色 */
	elog_set_text_color_enabled(true);
	/* 关闭缓冲区 */
	// elog_buf_enabled(false);
	/* 关闭异步输出 */
	// elog_async_enabled(false);
	/*  设置日志过滤器等级 */
	elog_set_filter_lvl(lvl);

	/* 断言：输出所有内容 */
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
	/* 错误：输出级别、标签和时间 */
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO & ~ELOG_FMT_DIR);
	/* 警告：输出级别、标签和时间 */
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO & ~ELOG_FMT_DIR);
	/* 信息：输出级别、标签和时间 */
	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO & ~ELOG_FMT_DIR);
	/* 调试：输出除了方法名之外的所有内容 */
	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO & ~ELOG_FMT_DIR);
	/* 详细：输出除了方法名之外的所有内容 */
	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO & ~ELOG_FMT_DIR);
	printf("hello 1\n");
	/* 启动日志系统 */
	elog_start();
	printf("hello 2\n");
	return 0;
}