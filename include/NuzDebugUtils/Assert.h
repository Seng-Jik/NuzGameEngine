#pragma once

#ifdef _DEBUG

/* 断言
 * Release下无效
 * @param 如果为false则报错并记录到LogErr
 */
void Assert(bool);

#else

#define Assert(x)

#endif


/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */