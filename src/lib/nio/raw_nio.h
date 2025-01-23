/**
 * @file raw_nio.h
 * @author owenchzh (ch.zhen@nlscan.com)
 * @brief
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022 owenr-owenchzh
 *
 */

#ifndef _raw_nio_H
#define _raw_nio_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
// nanomsg 通信协议
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/pubsub.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/survey.h>
#include <nanomsg/bus.h>
#include <nanomsg/ws.h>
// nanomsg 传输协议
#include <nanomsg/tcp.h>
#include <nanomsg/inproc.h>
#include <nanomsg/ipc.h>

#include "raw_log.h"

typedef enum {
	RAW_NIO_SERVICE = 0,
	RAW_NIO_CLIENT,
} NC_nnType;

typedef struct {
	int id;
	int fd;
} NC_nio;

typedef struct {
	uint32_t id;
	uint32_t size;
} NC_msgHdr;

/**
 * @brief 数据发送
 *
 * @param io
 * @param id
 * @param data
 * @param size
 * @return int
 */
int raw_nioSend(NC_nio io, uint32_t id, void* data, size_t size);

/**
 * @brief 数据接收
 *
 * @param io
 * @param id
 * @param data
 * @return int
 */
int raw_nioRecv(NC_nio io, uint32_t* id, void** data);
/**
 * @brief 释放内存
 *
 * @param data
 * @return int
 */
int raw_nioFree(void* data);
/**
 * @brief 关闭连接
 *
 * @param io
 * @return int
 */
int raw_nioClose(NC_nio io);
/**
 * @brief pubsub 通信模式
 *
 * @param link
 * @param type
 * @param id
 * @return int
 */
int raw_nioPubsub(char* link, NC_nnType type, NC_nio* io);
/**
 * @brief 订阅模式下的主题过滤
 *
 * @param io
 * @param tips 关心的主题
 * @return int
 */
int raw_nioPubSubTips(NC_nio* io, char* tips);
/**
 * @brief reqrep 通信模式
 *
 * @param link
 * @param type
 * @param id
 * @return int
 */
int raw_nioReqrep(char* link, NC_nnType type, NC_nio* io);
/**
 * @brief 调查者 通信模式
 *
 * @param link
 * @param type
 * @param id
 * @param timeout
 * @return int
 */
int raw_nioSurvey(char* link, NC_nnType type, NC_nio* io, size_t timeout);
/**
 * @brief 实现push/pull模式
 *
 * @param link
 * @param type
 * @param io
 * @return int
 */
int raw_nioPushPull(char* link, NC_nnType type, NC_nio* io);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _raw_nio_H