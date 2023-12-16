#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <windows.h>


#if defined(DEBUG) || defined(RELEASE)
/**
 * @brief 에러 코드에 대응하는 메시지를 얻습니다.
 * 
 * @param errorCode 확인할 에러 코드입니다.
 * 
 * @return 에러 코드에 대응하는 메시지를 반환합니다.
 */
std::string GetErrorCodeMessageA(const uint32_t& errorCode)
{
	static const uint32_t MAX_BUFFER_SIZE = 1024;
	static char buffer[MAX_BUFFER_SIZE];

	uint32_t size = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		static_cast<DWORD>(errorCode),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buffer,
		MAX_BUFFER_SIZE,
		nullptr
	);

	return std::string(buffer, size);
}


/**
 * @brief 에러 코드에 대응하는 메시지를 얻습니다.
 * 
 * @param errorCode 확인할 에러 코드입니다.
 *
 * @return 에러 코드에 대응하는 메시지를 반환합니다.
 */
std::wstring GetErrorCodeMessageW(const uint32_t& errorCode)
{
	static const uint32_t MAX_BUFFER_SIZE = 1024;
	static wchar_t buffer[MAX_BUFFER_SIZE];

	uint32_t size = FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		static_cast<DWORD>(errorCode),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buffer,
		MAX_BUFFER_SIZE,
		nullptr
	);

	return std::wstring(buffer, size);
}
#endif


/**
 * @brief Windows API 호출값을 검사합니다.
 * 
 * @param Expression 검사할 호출값입니다.
 * @param ... 평가식을 만족하지 못할 경우 표시할 가변 인자 메시지입니다.
 * 
 * @note
 * - Debug 모드와 Release 모드에서는 평가식을 검사하지만 Shipping 모드에서는 평가식을 검사하지 않습니다.
 * - 디버거가 존재하면 브레이크 포인트가 걸립니다.
 * - 디버거가 존재하지 않으면 크래시 덤프 파일을 생성합니다.
 */
#if defined(DEBUG)

#elif defined(RELEASE)

#else // defined(SHIPPING)

#endif