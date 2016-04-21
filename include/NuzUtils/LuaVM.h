#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* Lua�����
	 */
	class ILuaVM{
	public:
	
		/* ����Lua��׼�� */
		virtual void OpenLibMath() = 0;	//��ѧ
		virtual void OpenLibIO() = 0;	//IO
		virtual void OpenLibString() = 0;	//�ַ���
		virtual void OpenLibTable() = 0;	//��
		
		/* ���� */
		
		/* ���ر�����Lua
		 * @param ��������
		 * @param �ñ�����Lua�е�����
		 */
		virtual void MountNumber(int&,const std::string&) = 0;	//������ֵ
		virtual void MountNumber(double&,const std::string&) = 0;
		virtual void MountNumber(float&,const std::string&) = 0;
		virtual void MountString(std::string&,const std::string&) = 0;	//�����ַ���
		virtual void MountBool(bool&,const std::string&) = 0;	//�����߼�ֵ
		virtual void MountFunction(void (*func)(LuaVM&),const std::string&) = 0;	//���غ���
		
		/* ��Luaջȡ��ջ��
		 * @result ջ��Ԫ��
		 */
		virtual double PopNumber() = 0;	//ȡ����ֵ
		virtual std::string PopString() = 0;	//ȡ���ַ���
		virtual double PopBoolean() = 0;	//ȡ���߼�ֵ
		
		/* Luaѹջ
		 * @param ջ��Ԫ��
		 */
		virtual void PushNumber(double) = 0;	//ѹ����ֵ
		virtual void PushString(const std::string&) = 0;	//ѹ���ַ���
		virtual void PushBoolean(const std::string&) = 0;	//ѹ���߼�ֵ
		
		/* ���غ͵��ô��� */
		
		/* ���ش���
		 * @param ��������
		 */
		virtual void LoadProgram(const std::string& code) = 0;
		
		/* ���ú���
		 * ����ֵ�ᱻ����ջ��
		 * @param Lua������
		 */
		virtual void Call(const std::string& functionName) = 0;
		
		/* ����������
		 */
		virtual void Call() = 0;
	};
	
	/* ����Lua�����
	 * @result Lua�����
	 */
	std::shared_ptr<ILuaVM> CreateLuaVM();
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 */
