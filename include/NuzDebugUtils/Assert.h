#pragma once

#ifdef _DEBUG

/* ����
 * Release����Ч
 * @param ���Ϊfalse�򱨴���¼��LogErr
 */
void Assert(bool);

#else

#define Assert(x)

#endif


/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */