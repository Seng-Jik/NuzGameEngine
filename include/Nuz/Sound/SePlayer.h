#pragma once
#include <memory>

namespace Nuz{

	/* ��Ч������
	 */
	class ISePlayer{
	public:

		/* ������Ч
		 * @param path �ļ�
		 */
		virtual void Load(const std::string& path) = 0;

		/* ж����Ч
		 */
		virtual void Clear() = 0;

		/* ������Ч
		 * @param ����ʱ�������룩
		 */
		virtual void Play(int fadein = 0) = 0;

		/* ��ͣ��Ч
		 * @param ����ʱ�������룩
		 */
		virtual void Pause(int fadeout = 0) = 0;

		/* ������Ч
		 * @param ����ʱ�������룩
		 */
		virtual void Resume(int fadein = 0) = 0;

		/* ����������ֵ
		 * @param ������0-100��
		 */
		virtual void SetVolume(int) = 0;

		/* ֹͣ��Ч
		 */
		virtual void Stop() = 0;

        /* ����Se������
         * @result Se������
         */
        static std::shared_ptr<ISePlayer> CreateSePlayer();

        /* ����һ����Ч����ɺ��Զ����ա�
         * @param path �ļ�
         * @param volume ����
         * @param fadein ����ʱ�������룩
         */
        static void PlayAutoSe(const std::string& path,int volume,int fadein);
	};
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
