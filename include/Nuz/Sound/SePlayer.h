#pragma once
#include <memory>

namespace Nuz{

	/* 音效播放器
	 */
	class ISePlayer{
	public:

		/* 加载音效
		 * @param path 文件
		 */
		virtual void Load(const std::string& path) = 0;

		/* 卸载音效
		 */
		virtual void Clear() = 0;

		/* 播放音效
		 * @param 淡入时长（毫秒）
		 */
		virtual void Play(int fadein = 0) = 0;

		/* 暂停音效
		 * @param 淡出时长（毫秒）
		 */
		virtual void Pause(int fadeout = 0) = 0;

		/* 继续音效
		 * @param 淡入时长（毫秒）
		 */
		virtual void Resume(int fadein = 0) = 0;

		/* 设置音量峰值
		 * @param 音量（0-100）
		 */
		virtual void SetVolume(int) = 0;

		/* 停止音效
		 */
		virtual void Stop() = 0;

        /* 创建Se播放器
         * @result Se播放器
         */
        static std::shared_ptr<ISePlayer> CreateSePlayer();

        /* 播放一个音效，完成后自动回收。
         * @param path 文件
         * @param volume 音量
         * @param fadein 淡入时长（毫秒）
         */
        static void PlayAutoSe(const std::string& path,int volume,int fadein);
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
