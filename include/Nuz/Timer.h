#pragma once
#include <cstdint>
#include <memory>

namespace Nuz{
    /* 计时器
     * 该计时器从创建开始计时。
     */
    class Timer{
    public:
        /* 获取当前时间
         * @result 当前计时器时间
         */
        virtual uint64_t GetTime() const = 0;
        
        /* 重设时间
         * 执行该函数会导致计时器清零并重新开始计时
         */
        virtual void Reset() = 0;
    
        /* 创建以毫秒为单位的计时器
         * @result 计时器
         */
        std::shared_ptr<Timer> CreateMSTimer();
        
        /* 创建以帧为单位的计时器
         * @result 计时器
         */
        std::shared_ptr<Timer> CreateFrameTimer();
    };
}

/* 更新日志：
 * 2016年4月30日：
 * 星翼 初稿
 */