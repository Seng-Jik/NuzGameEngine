#pragma once
#include <string>
#include <ostream>

#ifdef _DEBUG

/* 记录普通日志
 * Release下无效
 * @param log 日志内容
 * @param module 日志来源组件
 */
void LogStd(const std::string& log,const std::string& module = "");

/* 普通日志的输出位置
 * Release下无效
 * @param 输出流
 */
void SetStdLogOutputStream(std::ostream&);

/* 在普通日志里添加过滤白名单
 * Release下无效
 * 默认情况下不允许任何模块输出日志
 * @param module 允许的模块
 */
void AddStdLogWhiteFliter(const std::string& module);

/* 清空普通日志白名单
 * Release下无效
 */
void ClearStdLogWhiteFliter();

#else

#define LogStd(...)
#define SetStdLogOutputStream(...)
#define AddStdLogWhiteFliter(...)
#define ClearStdLogWhiteFliter(...)

#endif

/* 记录错误日志
 * Release下仍然有效
 * @param log 日志内容
 * @param module 日志来源组件
 */
void LogErr(const std::string& log,const std::string& module = "");

/* 错误日志的输出位置
 * Release下仍然有效
 * @param 输出流
 */
void SetErrLogOutputStream(std::ostream&);

/* 在错误日志里添加过滤黑名单
 * Release下仍然有效
 * 默认情况下允许任何模块输出日志
 * @param module 不允许的模块
 */
void AddErrLogBlackFliter(const std::string& module);

/* 清空普通日志黑名单
 * Release下仍然有效
 */
void ClearErrLogBlackFliter();

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
 