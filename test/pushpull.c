/**
 * @file pushpull.c
 * @author ch.zhen (ch.zhen@newland.com.cn)
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025 owenr-newland
 *
 */
#include <stdint.h>
#include <unistd.h>
#include <uv.h>
#include "raw_nio.h"
#include "raw_log.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "push/pull"
#endif

#define PATH_PUSH_PULL "inproc:///var/run/pushpull"

typedef struct _my {
	uv_loop_t* loop;
	uv_poll_t  poll;
	uv_work_t  work2;
	uv_work_t  work3;
	NC_nio	   io1;
	NC_nio	   io2;
	NC_nio	   io3;
} nc_my_t;

static void _work2_callback(uv_work_t* req)
{
	// 异步任务逻辑
	nc_my_t* my = (nc_my_t*)req->data;
	uint32_t id = 0;
	char	 buff[1024];

	while (1) {
		id++;
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "2- hello world %d", id);
		// log_d("send: id=[%d],[%s]", id, buff);
		raw_nioSend(my->io2, id, buff, strlen(buff));
		usleep(1000 * 100);
	}
}

static void _work3_callback(uv_work_t* req)
{
	// 异步任务逻辑
	nc_my_t* my = (nc_my_t*)req->data;
	uint32_t id = 3000;
	char	 buff[1024];

	while (1) {
		id++;
		memset(buff, 0, sizeof(buff));
		// sprintf(buff, "3- hello world %d", id);
		// log_d("send: id=[%d],[%s]", id, buff);
		raw_nioSend(my->io3, id, NULL, 0);
		usleep(1000 * 100);
	}
}

static void _after_work_callback(uv_work_t* req, int status)
{
	// 任务完成后的处理逻辑
}

static void _poll_callback(uv_poll_t* handle, int status, int events)
{
	nc_my_t* my	  = (nc_my_t*)handle->data;
	void*	 buff = NULL;
	uint32_t id	  = 0;

	if (events & UV_READABLE) {
		raw_nioRecv(my->io1, &id, &buff);
		log_w("recv: id=[%d],[%s]", id, buff);
		raw_nioFree(buff);
	}
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
	nc_my_t my;

	raw_logInit(LOG_LVL_DEBUG);

	my.loop = uv_default_loop();

	raw_nioPushPull(PATH_PUSH_PULL, RAW_NIO_SERVICE, &my.io1); // pull
	raw_nioPushPull(PATH_PUSH_PULL, RAW_NIO_CLIENT, &my.io2);  // push
	raw_nioPushPull(PATH_PUSH_PULL, RAW_NIO_CLIENT, &my.io3);  // push

	uv_poll_init(my.loop, &my.poll, my.io1.fd);
	my.poll.data = &my;
	uv_poll_start(&my.poll, UV_READABLE, _poll_callback);

	uv_queue_work(my.loop, &my.work2, _work2_callback, _after_work_callback);
	my.work2.data = &my;
	uv_queue_work(my.loop, &my.work3, _work3_callback, _after_work_callback);
	my.work3.data = &my;

	uv_run(my.loop, UV_RUN_DEFAULT);
}
