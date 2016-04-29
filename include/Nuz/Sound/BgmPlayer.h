#pragma once
#include <memory>

namespace Nuz{

	/* BGM播放器
	 * 可以播放一个两段的音乐
	 * 设这两段为A和B，则播放方式为：
	 * ABBBBBBBBBB...无限循环
	 * A被称为头段（Header），
	 * B被称为循环段（Loop）。
	 */
	class IBgmPlayer{
	public:

		/* 加载头段
		 * @param path 文件
		 */
		virtual void LoadHeader(const std::string& path) = 0;

		/* 加载循环段
		 * @param path 文件
		 */
		virtual void LoadLoop(const std::string& path) = 0;

		/* 卸载音乐
		 */
		virtual void Clear() = 0;

		/* 播放音乐
		 * @param fadein 淡入时长（毫秒）
		 */
		virtual void Play(int fadein = 0) = 0;

		/* 暂停音乐
		 * @param fadeout 淡出时长（毫秒）
		 */
		virtual void Pause(int fadeout = 0) = 0;

		/* 继续音乐
		 * @param fadein 淡入时长（毫秒）
		 */
		virtual void Resume(int fadein = 0) = 0;

		/* 设置音量峰值
		 * @param 音量（0-100）
		 */
		virtual void SetVolume(int) = 0;

		/* 停止音乐
		 */
		virtual void Stop() = 0;

        /* 创建BGM播放器
         * @result 创建的BGM播放器
         */
        static std::shared_ptr<IBgmPlayer> CreateBgmPlayer();
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
