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
#define LOG_TAG "survey"
#endif

#define PATH_SURVEY "inproc:///var/run/survey"

typedef struct _my {
	uv_loop_t* loop;
	uv_poll_t  poll;
	uv_poll_t  poll2;
	uv_poll_t  poll3;
	uv_timer_t timer;
	NC_nio	   io1;
	NC_nio	   io2;
	NC_nio	   io3;
} nc_my_t;

static void _on_poll_services(uv_poll_t* handle, int status, int events)
{
	nc_my_t* my	  = (nc_my_t*)handle->data;
	void*	 buff = NULL;
	uint32_t id	  = 0;
	int		 rv	  = 0;

	if (events & UV_READABLE) {
		rv = raw_nioRecv(my->io1, &id, &buff);
		if (rv > 0) {
			log_d("recv: id=[%d],[%s]", id, buff);
		} else {
			log_e("recv: id=[%d],[%s]", id, buff);
		}

		raw_nioFree(buff);
	}
}

static void _on_poll2_clients(uv_poll_t* handle, int status, int events)
{
	nc_my_t* my	  = (nc_my_t*)handle->data;
	void*	 buff = NULL;
	uint32_t id	  = 0;

	if (events & UV_READABLE) {
		raw_nioRecv(my->io2, &id, &buff);
		log_d("recv: id=[%d],[%s]", id, buff);
		raw_nioFree(buff);
		char data[1024] = {0};
		memset(data, 0, sizeof(data));
		sprintf(data, "reply2: hello, %d", id);
		raw_nioSend(my->io2, id, data, strlen(data));
	}
}
static void _on_poll3_clients(uv_poll_t* handle, int status, int events)
{
	nc_my_t* my	  = (nc_my_t*)handle->data;
	void*	 buff = NULL;
	uint32_t id	  = 0;

	if (events & UV_READABLE) {
		raw_nioRecv(my->io3, &id, &buff);
		log_d("recv: id=[%d],[%s]", id, buff);
		raw_nioFree(buff);
		char data[1024] = {0};
		memset(data, 0, sizeof(data));
		sprintf(data, "reply3: hello, %d", id);
		raw_nioSend(my->io3, id, data, strlen(data));
	}
}
static uint32_t g_id = 0;
static void		_on_timer_cb(uv_timer_t* handle)
{
	nc_my_t* my = (nc_my_t*)handle->data;

	g_id++;
	raw_nioSend(my->io1, g_id, "hello", 5);

	uv_timer_start(&my->timer, _on_timer_cb, 1000, 1000);
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

	raw_nioSurvey(PATH_SURVEY, RAW_NIO_SERVICE, &my.io1, 2000); // survey service
	raw_nioSurvey(PATH_SURVEY, RAW_NIO_CLIENT, &my.io2, 0);		// survey client
	raw_nioSurvey(PATH_SURVEY, RAW_NIO_CLIENT, &my.io3, 0);		// survey client

	uv_poll_init(my.loop, &my.poll, my.io1.fd);
	my.poll.data = &my;
	uv_poll_start(&my.poll, UV_READABLE, _on_poll_services);

	uv_poll_init(my.loop, &my.poll2, my.io2.fd);
	my.poll2.data = &my;
	uv_poll_start(&my.poll2, UV_READABLE, _on_poll2_clients);

	uv_poll_init(my.loop, &my.poll3, my.io3.fd);
	my.poll3.data = &my;
	uv_poll_start(&my.poll3, UV_READABLE, _on_poll3_clients);

	uv_timer_init(my.loop, &my.timer);
	my.timer.data = &my;
	uv_timer_start(&my.timer, _on_timer_cb, 0, 0);

	uv_run(my.loop, UV_RUN_DEFAULT);
}
