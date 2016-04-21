#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* SnowRV阅读器
	 */
	class ISnowRVReader{
	public:
	
		/* 取得字符串常量
		 * @param 常量名
		 * @result 常量字符串
		 */
		virtual std::string GetString(const std::string&) = 0;
		
		/* 取得数值常量
		 * @param 常量名
		 * @result 常量数值
		 */
		virtual int GetInt(const std::string&) = 0;
		
		/* 取得浮点数常量
		 * @param 常量名
		 * @result 常量浮点数
		 */
		virtual double GetFloat(const std::string&) = 0;
	};
	
	/* 创建SnowRV阅读器
	 * @param RV文件
	 * @result RV阅读器
	 */
	std::shared_ptr<ISnowRVReader> CreateSnowRVReader(const std::string& path);
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 */
