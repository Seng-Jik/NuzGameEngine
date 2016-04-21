#pragma once
#include <memory>
#include <string>

namespace NuzUtils{
	
	/* UDP包 */
	struct UDPPacket{
		uint32_t ipAddress;	//IPv4地址
		uint16_t port;	//端口号
		std::shared_ptr<std::string> data;	//数据
	};
	
	/* 解析IP地址
	 * @param 字符串形式的IP或域名
	 * @result 解析得到的IPv4 IP地址。
	 */
	uint32_t ResolveIPAdress(const std::string&);
	
	/* UDP网络协议
	 */
	class IUDPNet{
	public:
		
		/* 发送数据
		 * @param UDP包
		 */
		virtual void Send(const UDPPacket&) = 0;
		
		/* 接收数据
		 * @param UDP包
		 */
		virtual void Recv(UDPPacket&) = 0;
	};
	
	/* 创建UDP服务器
	 * @param port 端口（为0则自动选择空端口）
	 * @result UDP服务器
	 */
	std::shared_ptr<IUDPNet> CreateUDPServer(uint16_t port);
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 */
