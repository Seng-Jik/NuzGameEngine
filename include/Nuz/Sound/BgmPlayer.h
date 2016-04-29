#pragma once
#include <memory>

namespace Nuz{

	/* BGM������
	 * ���Բ���һ�����ε�����
	 * ��������ΪA��B���򲥷ŷ�ʽΪ��
	 * ABBBBBBBBBB...����ѭ��
	 * A����Ϊͷ�Σ�Header����
	 * B����Ϊѭ���Σ�Loop����
	 */
	class IBgmPlayer{
	public:

		/* ����ͷ��
		 * @param path �ļ�
		 */
		virtual void LoadHeader(const std::string& path) = 0;

		/* ����ѭ����
		 * @param path �ļ�
		 */
		virtual void LoadLoop(const std::string& path) = 0;

		/* ж������
		 */
		virtual void Clear() = 0;

		/* ��������
		 * @param fadein ����ʱ�������룩
		 */
		virtual void Play(int fadein = 0) = 0;

		/* ��ͣ����
		 * @param fadeout ����ʱ�������룩
		 */
		virtual void Pause(int fadeout = 0) = 0;

		/* ��������
		 * @param fadein ����ʱ�������룩
		 */
		virtual void Resume(int fadein = 0) = 0;

		/* ����������ֵ
		 * @param ������0-100��
		 */
		virtual void SetVolume(int) = 0;

		/* ֹͣ����
		 */
		virtual void Stop() = 0;

        /* ����BGM������
         * @result ������BGM������
         */
        static std::shared_ptr<IBgmPlayer> CreateBgmPlayer();
	};
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
