#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <windows.h>

#include "IManager.h"


/**
 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class FileManager : public IManager
{
public:
	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(FileManager);


	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return ���� �� ���丮 ó���� �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static FileManager& Get()
	{
		static FileManager instance;
		return instance;
	}


	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� ���� ��θ� ����ϴ�.
	 * 
	 * @return ���� ���� ��θ� ��ȯ�մϴ�.
	 */
	const std::wstring& GetExecutePath() const { return executePath_; }


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return ������ ���� ���͸� ��ȯ�մϴ�.
	 * 
	 * @see 
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	std::vector<uint8_t> ReadBufferFromFile(const std::string& path);


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return ������ ���� ���͸� ��ȯ�մϴ�.
	 * 
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	std::vector<uint8_t> ReadBufferFromFile(const std::wstring& path);
	

private:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(FileManager);


private:
	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	std::wstring executePath_;
};