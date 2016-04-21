#pragma once
#include <memory>
#include <string>

namespace NuzUtils{
	
	/* UDP�� */
	struct UDPPacket{
		uint32_t ipAddress;	//IPv4��ַ
		uint16_t port;	//�˿ں�
		std::shared_ptr<std::string> data;	//����
	};
	
	/* ����IP��ַ
	 * @param �ַ�����ʽ��IP������
	 * @result �����õ���IPv4 IP��ַ��
	 */
	uint32_t ResolveIPAdress(const std::string&);
	
	/* UDP����Э��
	 */
	class IUDPNet{
	public:
		
		/* ��������
		 * @param UDP��
		 */
		virtual void Send(const UDPPacket&) = 0;
		
		/* ��������
		 * @param UDP��
		 */
		virtual void Recv(UDPPacket&) = 0;
	};
	
	/* ����UDP������
	 * @param port �˿ڣ�Ϊ0���Զ�ѡ��ն˿ڣ�
	 * @result UDP������
	 */
	std::shared_ptr<IUDPNet> CreateUDPServer(uint16_t port);
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 */
