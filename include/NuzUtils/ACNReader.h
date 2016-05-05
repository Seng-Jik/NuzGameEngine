#pragma once
#include <memory>
#include <string>
#include <cstdint>

namespace NuzUtils{

	/* ACN树形配置文件阅读器
	 */
	class IACNReader{
	public:
        /* 树创建指导指令 */
        /* 树根由阅读器指导创建。 */
        /* 可能会有多个树根，这由你的配置文件决定。 */
        /* 请编写安全的代码来接受阅读器指导创建树。 */
        enum class ACNOpr{
            PushAndCreateNode = 0x00,  //将当前节点指针压栈并在当前节点下创建一个新的节点，将新节点设为当前节点，参数为节点名
            Pop = 0x01,    //设置栈顶的节点指针为当前节点指针，并弹出栈顶，参数无意义
            CreateVar = 0x10,  //为当前节点创建一个属性，参数为属性名，并设置为当前属性
            AddVal = 0x11,  //为当前属性添加一个值，参数为值
            End = 0xFF //树创建结束，无意义
        };

        /* 取得一个指导指令
         * @param 指令参数
         * @result 指令
         */
        virtual ACNOpr GetOpr(std::string& arg) noexcept = 0;

        /* 从头重新读取指导指令
         */
        virtual void Reset() noexcept = 0;

		/* 存储到高速读取的二进制文件中
		 * @param 文件路径
		 * @throw IFileSystem::CannotOpenFile
		 * @throw IFileSystem::InvaildFileName
		 */
        virtual void SaveToBinaryFile(const std::string&) const = 0;

        /* 取得该ACN文件所在目录
		 * @result 目录
		 */
        virtual std::string GetCurrentDir() const noexcept = 0;

        /* 异常类：无效ACN */
        class InvalidACN:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* 从文件创建ACN文件读取器
         * @param path ACN文件路径
         * @throw InvalidACN
         * @result ACN文件读取器
         */
        static std::shared_ptr<IACNReader> CreateACNReader(const std::string& path);
	};
}

/* 更新日志：
 * 2016年5月4日：
 * 星翼 初稿
 */
