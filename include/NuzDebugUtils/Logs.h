#pragma once
#include <string>
#include <ostream>

#ifdef _DEBUG

/* ��¼��ͨ��־
 * Release����Ч
 * @param log ��־����
 * @param module ��־��Դ���
 */
void LogStd(const std::string& log,const std::string& module = "");

/* ��ͨ��־�����λ��
 * Release����Ч
 * @param �����
 */
void SetStdLogOutputStream(std::ostream&);

/* ����ͨ��־����ӹ��˰�����
 * Release����Ч
 * Ĭ������²������κ�ģ�������־
 * @param module �����ģ��
 */
void AddStdLogWhiteFliter(const std::string& module);

/* �����ͨ��־������
 * Release����Ч
 */
void ClearStdLogWhiteFliter();

#else

#define LogStd(...)
#define SetStdLogOutputStream(...)
#define AddStdLogWhiteFliter(...)
#define ClearStdLogWhiteFliter(...)

#endif

/* ��¼������־
 * Release����Ȼ��Ч
 * @param log ��־����
 * @param module ��־��Դ���
 */
void LogErr(const std::string& log,const std::string& module = "");

/* ������־�����λ��
 * Release����Ȼ��Ч
 * @param �����
 */
void SetErrLogOutputStream(std::ostream&);

/* �ڴ�����־����ӹ��˺�����
 * Release����Ȼ��Ч
 * Ĭ������������κ�ģ�������־
 * @param module �������ģ��
 */
void AddErrLogBlackFliter(const std::string& module);

/* �����ͨ��־������
 * Release����Ȼ��Ч
 */
void ClearErrLogBlackFliter();

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
 