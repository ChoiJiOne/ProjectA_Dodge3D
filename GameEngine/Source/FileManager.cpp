#include "FileManager.h"

#include "Assertion.h"
#include "StringUtils.h"
#include "WindowsAssertion.h"

void FileManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup file manager...");

	wchar_t* bufferPtr = StringUtils::GetWideCharBufferPtr();
	WINDOWS_ASSERT(GetModuleFileNameW(nullptr, bufferPtr, StringUtils::STRING_BUFFER_SIZE), "failed to get execute file name...");

	executePath_ = std::wstring(bufferPtr);

	bIsStartup_ = true;
}

void FileManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}

std::vector<uint8_t> FileManager::ReadBufferFromFile(const std::string& path)
{
	HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	WINDOWS_ASSERT(fileHandle != INVALID_HANDLE_VALUE, "failed to open %s", path.c_str());

	DWORD fileSize = GetFileSize(fileHandle, nullptr);
	std::vector<uint8_t> buffer(fileSize);

	DWORD bytesRead;
	WINDOWS_ASSERT(ReadFile(fileHandle, &buffer[0], fileSize, &bytesRead, nullptr), "failed to read %s", path.c_str());
	WINDOWS_ASSERT(CloseHandle(fileHandle), "failed to close %s", path.c_str());

	return buffer;
}

std::vector<uint8_t> FileManager::ReadBufferFromFile(const std::wstring& path)
{
	HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	WINDOWS_ASSERT(fileHandle != INVALID_HANDLE_VALUE, L"failed to open %s", path.c_str());

	DWORD fileSize = GetFileSize(fileHandle, nullptr);
	std::vector<uint8_t> buffer(fileSize);

	DWORD bytesRead;
	WINDOWS_ASSERT(ReadFile(fileHandle, &buffer[0], fileSize, &bytesRead, nullptr), L"failed to read %s", path.c_str());
	WINDOWS_ASSERT(CloseHandle(fileHandle), L"failed to close %s", path.c_str());

	return buffer;
}