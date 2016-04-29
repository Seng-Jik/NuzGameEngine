#pragma once

namespace Nuz{
	/* ������ */
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

	/* �������������
	 * ����������е������豸
	 */
	class IKeyboard{
	public:
		/* ��ȡĳ�����Ƿ��Ѿ�����
		 * @param ����
		 * @result �Ƿ��Ѿ�����
		 */
		virtual bool KeyPressed(KeyCode) const = 0;
	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 *
 */
