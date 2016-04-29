#pragma once
#include <string>
#include <ostream>
namespace Nuz{

    /* 记录普通日志
     * @param log 日志内容
     * @param module 日志来源组件
     */
    void LogStd(const std::string& log,const std::string& module = "");

    /* 普通日志的输出位置
     * 默认是cout流
     * @param 输出流
     */
    void SetStdLogOutputStream(std::ostream&) noexcept;

    /* 在普通日志里添加过滤白名单
     * 默认情况下不允许任何模块输出日志，没有模块名的除外
     * @param module 允许的模块
     */
    void AddStdLogWhiteFliter(const std::string& module);

    /* 清空普通日志白名单
     */
    void ClearStdLogWhiteFliter();

    /* 记录错误日志
     * Release下仍然有效
     * @param log 日志内容
     * @param module 日志来源组件
     */
    void LogErr(const std::string& log,const std::string& module = "");

    /* 错误日志的输出位置
     * 默认是cerr流
     * Release下仍然有效
     * @param 输出流
     */
    void SetErrLogOutputStream(std::ostream&) noexcept;

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

}