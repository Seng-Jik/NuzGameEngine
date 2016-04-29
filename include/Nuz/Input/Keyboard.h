#pragma once

namespace Nuz{
	/* 按键表 */
	enum class KeyCode{
		ESC,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
		K1,K2,K3,K4,K5,K6,K7,K8,K9,K0,KSub,KAdd,KBackspace,
		Tab,Q,W,E,R,T,Y,U,I,O,P,LCK,RCK,ENTER,
		CapsLock,A,S,D,F,G,H,J,K,L,Split,UDot,Or,
		LShift,Z,X,C,V,B,N,M,Comma,Dot,Div,RShift,
		LCtrl,LWin,LAlt,Space,RAlt,RWin,Menu,RCtrl,
		Up,
		Left,Down,Right,
		NumLock,NDiv,NMul,NSub,NAdd,NEnter,
		N7,N8,N9,
		N4,N5,N6,
		N1,N2,N3,
		N0,NDot
	};

	/* 键盘输入管理器
	 * 负责管理所有的输入设备
	 */
	class IKeyboard{
	public:
		/* 获取某个键是否已经按下
		 * @param 按键
		 * @result 是否已经按下
		 */
		virtual bool KeyPressed(KeyCode) const = 0;
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 *
 */
