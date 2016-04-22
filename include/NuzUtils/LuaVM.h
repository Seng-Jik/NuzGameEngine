#pragma once
#include <memory>
#include <string>

struct lua_State;
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
		 * Ҫ���صı������볤�ڴ���
		 * @param ��������
		 * @param �ñ�����Lua�е�����
		 */
		virtual void MountNumber(int&,const std::string&) = 0;	//������ֵ
		virtual void MountNumber(double&,const std::string&) = 0;
		virtual void MountNumber(float&,const std::string&) = 0;
		virtual void MountString(std::string&,const std::string&) = 0;	//�����ַ���
		virtual void MountBool(bool&,const std::string&) = 0;	//�����߼�ֵ

		/* ���غ�����Lua
		 * @param func C��������Lua�ĵ���
		 * @param ����Lua�����е�����
		 */
		virtual void MountFunction(int(*func)(lua_State*),const std::string&) = 0;	//���غ���

		/* ���غ͵��ô��� */

		/* ���ش���
		 * @param code ��������
		 */
		virtual void LoadProgram(const std::string& code) = 0;

		/* ���ش��루���ļ���
		 * @param �ļ���
		 * @throw Nuz::CannotOpenFile
		 * @throw Nuz::InvaildFileName
		 */
        virtual void LoadProgramFromFile(const std::string&) = 0;

		/* ���ú���
		 * ����ֵ�ᱻ����ջ��
		 * @param functionName Lua������
         * @param argc ��������
         * @param nresults ����ֵ����
		 */
		virtual void Call(const std::string& functionName,int argc,int nresults) = 0;

		/* ����������
		 */
		virtual void Call() = 0;

		/* ȡ��Lua�����ָ��
		 * @result lua_State* ָ��
		 */
        virtual lua_State* GetLuaState() = 0;
	};

	/* ����Lua�����
	 * @result Lua�����
	 */
	std::shared_ptr<ILuaVM> CreateLuaVM();
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 * ���� ������ļ�����
 */
