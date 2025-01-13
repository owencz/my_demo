# 实现程序崩溃后的处理机制
# 基本思路：
	1、监听系统崩溃的信号
	2、使用基于libunwind的堆栈解析库，回溯堆栈信息

# 涉及的崩溃信号
	SIGSEGV: 段错误
	SIGBUS:  总线错误
	SIGFPE:  浮点异常
	SIGILL:  非法指令
	SIGABRT: 断言失败

# 涉及的终端正常退出信号
	SIGTERM: 终端请求
	SIGINT:  中断请求
	SIGQUIT: 退出请求