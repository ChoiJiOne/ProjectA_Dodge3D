#include <shlwapi.h>

#include "Assertion.h"
#include "FileUtils.h"
#include "StringUtils.h"


std::vector<uint8_t> FileUtils::ReadBufferFromFile(const std::string& path)
{
	HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	WINDOWS_ASSERT(fileHandle != INVALID_HANDLE_VALUE, "failed to open %s...", path.c_str());

	DWORD fileSize = GetFileSize(fileHandle, nullptr);
	std::vector<uint8_t> buffer(fileSize);

	DWORD bytesRead;
	WINDOWS_ASSERT(ReadFile(fileHandle, &buffer[0], fileSize, &bytesRead, nullptr), "failed to read %s...", path.c_str());
	WINDOWS_ASSERT(CloseHandle(fileHandle), "failed to close %s...", path.c_str());

	return buffer;
}

std::vector<uint8_t> FileUtils::ReadBufferFromFile(const std::wstring& path)
{
	HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	WINDOWS_ASSERT(fileHandle != INVALID_HANDLE_VALUE, L"failed to open %s...", path.c_str());

	DWORD fileSize = GetFileSize(fileHandle, nullptr);
	std::vector<uint8_t> buffer(fileSize);

	DWORD bytesRead;
	WINDOWS_ASSERT(ReadFile(fileHandle, &buffer[0], fileSize, &bytesRead, nullptr), L"failed to read %s...", path.c_str());
	WINDOWS_ASSERT(CloseHandle(fileHandle), L"failed to close %s...", path.c_str());

	return buffer;
}

void FileUtils::WriteBufferToFile(const std::string& path, const std::vector<uint8_t>& buffer)
{
	HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	WINDOWS_ASSERT(fileHandle != INVALID_HANDLE_VALUE, "failed to create %s...", path.c_str());

	DWORD writeByteSize = 0;
	WINDOWS_ASSERT(WriteFile(fileHandle, &buffer[0], static_cast<DWORD>(buffer.size()), &writeByteSize, nullptr), "failed to write %s...", path.c_str());
	WINDOWS_ASSERT(CloseHandle(fileHandle), "failed to close %s...", path.c_str());
}

void FileUtils::WriteBufferToFile(const std::wstring& path, const std::vector<uint8_t>& buffer)
{
	HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	WINDOWS_ASSERT(fileHandle != INVALID_HANDLE_VALUE, L"failed to create %s...", path.c_str());

	DWORD writeByteSize = 0;
	WINDOWS_ASSERT(WriteFile(fileHandle, &buffer[0], static_cast<DWORD>(buffer.size()), &writeByteSize, nullptr), L"failed to write %s...", path.c_str());
	WINDOWS_ASSERT(CloseHandle(fileHandle), L"failed to close %s...", path.c_str());
}

bool FileUtils::IsValidPath(const std::string& path)
{
	return PathFileExistsA(path.c_str());
}

bool FileUtils::IsValidPath(const std::wstring& path)
{
	return PathFileExistsW(path.c_str());
}

std::string FileUtils::GetBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return "";
	}
}

std::wstring FileUtils::GetBasePath(const std::wstring& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind(L'/')) != std::wstring::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind(L'\\')) != std::wstring::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return L"";
	}
}

std::string FileUtils::RemoveBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else
	{
		return path;
	}
}

std::wstring FileUtils::RemoveBasePath(const std::wstring& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind(L'/')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else if ((lastSlash = path.rfind(L'\\')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else
	{
		return path;
	}
}

std::string FileUtils::GetFileExtension(const std::string& path)
{
	std::string filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::string::npos) ? "" : filename.substr(offset + 1);
}

std::wstring FileUtils::GetFileExtension(const std::wstring& path)
{
	std::wstring filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::wstring::npos) ? L"" : filename.substr(offset + 1);
}

Json::Value FileUtils::ReadJsonFromFile(const std::string& path)
{
	std::vector<uint8_t> jsonBuffer = ReadBufferFromFile(path);
	std::string jsonString(jsonBuffer.begin(), jsonBuffer.end());

	Json::Value root;
	Json::Reader reader;
	ASSERT(reader.parse(jsonString, root), "failed to parse %s json file...", path.c_str());

	return root;
}

Json::Value FileUtils::ReadJsonFromFile(const std::wstring& path)
{
	std::vector<uint8_t> jsonBuffer = ReadBufferFromFile(path);
	std::string jsonString(jsonBuffer.begin(), jsonBuffer.end());

	Json::Value root;
	Json::Reader reader;
	ASSERT(reader.parse(jsonString, root), L"failed to parse %s json file...", path.c_str());

	return root;
}