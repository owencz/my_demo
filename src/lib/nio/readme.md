# 基于nanomsg的通信接口封装
	1、PUB/SUB模式
		用于发布TOPIC主题，多个SUB订阅端订阅Topic后，收到Topic数据
	2、REQ/REP模式
		用于多个请求端推送数据，REP接收端接收数据后立即应答
	3、PUSH/PULL模式
		用于多个PUSH端推送数据，多个PULL端或单个接收端接收数据
	4、SURVERY模式
		调查者模式，用于单个SURVERY端推送数据，多个REPLY端接收数据后，收到所有数据后，立即应答
