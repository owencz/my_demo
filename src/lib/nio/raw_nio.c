/**
 * @file raw_nio.c
 * @author owenchzh (ch.zhen@nlscan.com)
 * @brief
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022 owenr-owenchzh
 *
 */
#include "raw_nio.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "raw_nio"
#endif

/**
 * @brief 数据发送
 *
 * @param io
 * @param id
 * @param data
 * @param size
 * @return int
 */
int raw_nioSend(NC_nio io, uint32_t id, void* data, size_t size)
{
	NC_msgHdr		 head;
	struct nn_msghdr hdr;
	struct nn_iovec	 iov[2];

	head.id	  = id;
	head.size = size;

	iov[0].iov_base = &head;
	iov[0].iov_len	= sizeof(head);
	iov[1].iov_base = data;
	iov[1].iov_len	= size;
	memset(&hdr, 0, sizeof(hdr));
	hdr.msg_iov	   = iov;
	hdr.msg_iovlen = 2;

	int rv = nn_sendmsg(io.id, &hdr, 0);
	// log_d("id=%d,size=%d,rv=%d,data=%s", id, size, rv, data);
	return 0;
}

/**
 * @brief 数据接收
 *
 * @param io
 * @param id
 * @param data
 * @param szie
 * @return int
 */
int raw_nioRecv(NC_nio io, uint32_t* id, void* data, size_t size)
{
	NC_msgHdr		 head;
	struct nn_msghdr hdr;
	struct nn_iovec	 iov[2];

	iov[0].iov_base = &head;
	iov[0].iov_len	= sizeof(id);
	iov[1].iov_base = data;
	iov[1].iov_len	= size;
	memset(&hdr, 0, sizeof(hdr));
	hdr.msg_iov	   = iov;
	hdr.msg_iovlen = 2;

	int rv = nn_recvmsg(io.id, &hdr, 0);
	*id	   = head.id;
	size   = head.size;
	// log_d("id=%d,size=%d,rv=%d,data=%s", *id, size, rv, data);

	return size;
}

/**
 * @brief
 *
 * @param io
 * @return int
 */
int raw_nioClose(NC_nio io)
{
	nn_close(io.id);
	return 0;
}
/**
 * @brief pubsub 通信模式
 *
 * @param link
 * @param type
 * @param id
 * @return int
 */
int raw_nioPubsub(char* link, NC_nnType type, NC_nio* io)
{
	size_t optlen = sizeof(size_t);
	io->fd		  = -1;

	if (type == RAW_NIO_CLIENT) {
		if ((io->id = nn_socket(AF_SP, NN_SUB)) < 0) {
			log_e("nn_socket:%s", strerror(errno));
		}
		if (nn_setsockopt(io->id, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) < 0) {
			log_e("nn_setsockopt:%s", strerror(errno));
			return -1;
		}
		if (nn_connect(io->id, link) < 0) {
			log_e("nn_connect:%s", strerror(errno));
			return -1;
		}
		/*获取到对应的fd句柄*/
		if (nn_getsockopt(io->id, NN_SOL_SOCKET, NN_RCVFD, &io->fd, &optlen) < 0) {
			log_e("nn_setsockopt:%s", strerror(errno));
			return -1;
		}
	} else {
		if ((io->id = nn_socket(AF_SP, NN_PUB)) < 0) {
			log_e("nn_socket:%s", strerror(errno));
		}
		if (nn_bind(io->id, link) < 0) {
			log_e("nn_bind:%s", strerror(errno));
			return -1;
		}
	}

	log_d("link=%s:%s,id=%d,fd=%d", link, (type ? "client" : "service"), io->id, io->fd);

	return 0;
}
/**
 * @brief 订阅模式下的主题过滤
 *
 * @param io
 * @param tips 关心的主题
 * @return int
 */
int raw_nioPubSubTips(NC_nio* io, char* tips)
{
	if (nn_setsockopt(io->id, NN_SUB, NN_SUB_SUBSCRIBE, tips, strlen(tips)) < 0) {
		log_e("tips:%s", strerror(errno));
		return -1;
	}
}

/**
 * @brief reqrep 通信模式
 *
 * @param link
 * @param type
 * @param id
 * @return int
 */
int raw_nioReqrep(char* link, NC_nnType type, NC_nio* io)
{
	io->fd = -1;

	if (type == RAW_NIO_CLIENT) {
		if ((io->id = nn_socket(AF_SP, NN_REQ)) < 0) {
			log_e("nn_socket:%s", strerror(errno));
		}
		if (nn_connect(io->id, link) < 0) {
			log_e("nn_connect:%s", strerror(errno));
			return -1;
		}
	} else {
		if ((io->id = nn_socket(AF_SP, NN_REP)) < 0) {
			log_e("nn_socket:%s", strerror(errno));
		}
		if (nn_bind(io->id, link) < 0) {
			log_e("nn_bind:%s", strerror(errno));
			return -1;
		}
		/*获取到对应的fd句柄*/
		size_t optlen = sizeof(size_t);
		if (nn_getsockopt(io->id, NN_SOL_SOCKET, NN_RCVFD, &io->fd, &optlen) < 0) {
			log_e("nn_setsockopt:%s", strerror(errno));
			return -1;
		}
	}

	log_d("link=%s:%s,id=%d,fd=%d", link, (type ? "client" : "service"), io->id, io->fd);

	return 0;
}

/**
 * @brief 调查者 通信模式
 *
 * @param link
 * @param type
 * @param id
 * @return int
 */
int raw_nioSurvey(char* link, NC_nnType type, NC_nio* io)
{
	if (type == RAW_NIO_CLIENT) {
		if ((io->id = nn_socket(AF_SP, NN_RESPONDENT)) < 0) {
			log_e("nn_socket:%s", strerror(errno));
		}
		if (nn_connect(io->id, link) < 0) {
			log_e("nn_connect:%s", strerror(errno));
			return -1;
		}
		/*获取到对应的fd句柄*/
		size_t optlen = sizeof(size_t);
		if (nn_getsockopt(io->id, NN_SOL_SOCKET, NN_RCVFD, &io->fd, &optlen) < 0) {
			log_e("nn_setsockopt:%s", strerror(errno));
			return -1;
		}
	} else {
		if ((io->id = nn_socket(AF_SP, NN_SURVEYOR)) < 0) {
			log_e("nn_socket:%s", strerror(errno));
		}
		if (nn_bind(io->id, link) < 0) {
			log_e("nn_bind:%s", strerror(errno));
			return -1;
		}
	}

	log_d("link=%s:%s,id=%d,fd=%d", link, (type ? "client" : "service"), io->id, io->fd);

	return 0;
}

/**
 * @brief 实现push/pull模式
 *
 * @param link
 * @param type
 * @param io
 * @return int
 */
int raw_nioPushPull(char* link, NC_nnType type, NC_nio* io)
{
	if (type == RAW_NIO_CLIENT) {
		// PUSH
		if ((io->id = nn_socket(AF_SP, NN_PUSH)) < 0) {
			log_e("nn_socket");
			return -1;
		}
		if (nn_connect(io->id, link) < 0) {
			log_e("nn_connect");
			return -1;
		}
	} else {
		// PULL
		if ((io->id = nn_socket(AF_SP, NN_PULL)) < 0) {
			log_e("nn_socket");
			return -1;
		}
		if (nn_bind(io->id, link) < 0) {
			log_e("nn_bind");
			return -1;
		}
		/*获取到对应的fd句柄*/
		size_t optlen = sizeof(size_t);
		if (nn_getsockopt(io->id, NN_SOL_SOCKET, NN_RCVFD, &io->fd, &optlen) < 0) {
			log_e("nn_setsockopt");
			return -1;
		}
	}
	log_d("link=%s:%s,id=%d,fd=%d", link, (type ? "client" : "service"), io->id, io->fd);
	return 0;
}
