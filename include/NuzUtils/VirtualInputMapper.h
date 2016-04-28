#pragma once
#include <memory>
#include <string>

namespace Nuz{
	enum class KeyCode;
	class IKeyboard;
	class IGamePad;
}

namespace NuzUtils{

	/* 虚拟控制器
	 * 它是一个三维向量组（三个值范围均为-32768~32767）
	 * 对于按键，可绑定不同方向的值
	 * 对于摇杆，可以绑定到X和Y方向
	 * 对于鼠标和触屏，则为比率，中心点为(0,0)。
	 * 保证至少有一个向量
	 */
	class IVirtualInputMapper{
	public:

		/* 获得各方向分向量
		 * @param 向量编号
		 * @result 分向量模长
		 */
		virtual int GetX() = 0;	//X方向
		virtual int GetY() = 0;	//Y方向
		virtual int GetZ() = 0;	//Z方向

		/* 获得向量个数
		 * @result 向量个数
		 */
		virtual int GetVectorNum() = 0;

		/* 设置向量个数
		 * @param 向量个数
		 */
		virtual void SetVectorNum(int) = 0;

		/* 绑定键盘按键到向量
		 * @param 键盘指针
		 * @param 键盘按键
		 * @param vectorNum 向量编号
		 * @param useX 占用X方向
		 * @param x 占用时X的值
		 * @param useY 占用Y方向
		 * @param y 占用时Y的值
		 * @param useZ 占用Z方向
		 * @param z 占用Z方向的值
		 */
		virtual void BindKeyboardKey(
			std::shared_ptr<IKeyboard>,
			KeyCode,
			int vectorNum,
			bool useX,int x,
			bool useY,int y,
			bool useZ,int z
		) = 0;

		/* 绑定手柄按键到向量
		 * @param 手柄指针
		 * @param key 手柄按键
		 * @param vectorNum 向量编号
		 * @param useX 占用X方向
		 * @param x 占用时X的值
		 * @param useY 占用Y方向
		 * @param y 占用时Y的值
		 * @param useZ 占用Z方向
		 * @param z 占用Z方向的值
		 */
		virtual void BindGamePadKey(
			std::shared_ptr<IGamePad>,
			int key,
			int vectorNum,
			bool useX,int x,
			bool useY,int y,
			bool useZ,int z
		) = 0;

		/* 绑定摇杆或十字键到X和Y方向
		 * @param 摇杆或十字键指针
		 * @param vectorNum 向量编号
		 */
		virtual void BindJoystick(
			std::shared_ptr<IJoystick>,
			int vectorNum;
		) = 0;


        /* 虚拟输入设备
         * @param 向量个数
         * @result 虚拟输入设备
         */
        static std::shared_ptr<IVirtualInputMapper> CreateVirtualInputMapper(int);
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 */
