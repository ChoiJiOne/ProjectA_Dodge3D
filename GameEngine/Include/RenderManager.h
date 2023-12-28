#pragma once

#include <cstdint>
#include <unordered_map>
#include <windows.h>

#include "IManager.h"
#include "Matrix4x4.h"

class Window;
class Shader;
class Mesh;


/**
 * @brief 렌더링 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 * 
	 * @return 렌더링 처리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static RenderManager& Get()
	{
		static RenderManager instance;
		return instance;
	}


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 시작합니다.
	 * 
	 * @note 
	 * - 이 메서드 호출 전에 렌더링 대상이 되는 윈도우 포인터를 설정해야 합니다.
	 * - 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 종료합니다.
	 * 
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 렌더링 대상이 되는 윈도우를 설정합니다.
	 * 
	 * @param window 렌더링 대상이 되는 윈도우입니다.
	 */
	void SetRenderTargetWindow(Window* window) { renderTargetWindow_ = window; }


	/**
	 * @brief 렌더링 대상이 되는 윈도우를 얻습니다.
	 * 
	 * @return 렌더링 대상이 되는 윈도우의 포인터를 반환합니다.
	 */
	Window* GetRenderTargetWindow() const { return renderTargetWindow_; }


	/**
	 * @brief 프레임 렌더링을 시작합니다.
	 * 
	 * @param red 색상 버퍼의 R 값입니다.
	 * @param green 색상 버퍼의 G 값입니다.
	 * @param blue 색상 버퍼의 B 값입니다.
	 * @param alpha 색상 버퍼의 A 값입니다.
	 * @param depth 깊이 버퍼의 초기화 값입니다.
	 * @param stencil 스텐실 버퍼의 초기화 값입니다.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief 백버퍼와 프론트 버퍼를 스왑합니다.
	 */
	void EndFrame();


	/**
	 * @brief 뷰 포트를 설정합니다.
	 * 
	 * @param x 뷰포트 사각형의 왼쪽 아래 모서리(픽셀)입니다. 기본값은 (0,0)입니다.
	 * @param y 뷰포트 사각형의 왼쪽 아래 모서리(픽셀)입니다. 기본값은 (0,0)입니다.
	 * @param width 뷰포트의 너비입니다. OpenGL 컨텍스트가 창에 처음 연결되면 너비 와 높이 가 해당 창의 크기로 설정됩니다.
	 * @param height 뷰포트의 높이입니다. OpenGL 컨텍스트가 창에 처음 연결되면 너비 와 높이 가 해당 창의 크기로 설정됩니다.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * @brief 수직 동기화 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 수직 동기화 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief 깊이 테스트 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 깊이 테스트 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief 스텐실 테스트 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 스텐실 테스트 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetStencilMode(bool bIsEnable);


	/**
	 * @brief 알파 블랜딩 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 알파 블랜딩 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetAlphaBlendMode(bool bIsEnable);


	/**
	 * @brief 3D 메시를 정점 색상을 이용해서 화면에 그립니다.
	 * 
	 * @param world 월드 행렬입니다.
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param mesh 화면에 그릴 메시 리소스입니다.
	 */
	void RenderMesh3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, const Mesh* mesh);


private:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief 렌더링 대상이 되는 윈도우 포인터입니다.
	 */
	Window* renderTargetWindow_ = nullptr;


	/**
	 * @brief 수직 동기화 활성화 여부입니다. 기본 값은 비활성화입니다.
	 */
	bool bIsEnableVsync_ = false;


	/**
	 * @brief 깊이 테스트 활성화 여부입니다. 기본 값은 활성화입니다.
	 */
	bool bIsEnableDepth_ = true;


	/**
	 * @brief 스텐실 테스트 활성화 여부입니다. 기본 값은 비활성화입니다.
	 */
	bool bIsEnableStencil_ = false;


	/**
	 * @brief 알파 블랜딩 활성화 여부입니다. 기본 값은 활성화입니다.
	 */
	bool bIsEnableAlphaBlend_ = true;


	/**
	 * @brief 렌더링이 수행될 디바이스 컨텍스트의 핸들입니다.
	 */
	HDC deviceContext_ = nullptr;


	/**
	 * @brief 렌더링이 수행될 OpenGL 컨텍스트의 핸들입니다.
	 */
	HGLRC glRenderContext_ = nullptr;


	/**
	 * @brief 셰이더 리소스의 경로입니다.
	 */
	std::wstring shaderPath_;

	
	/**
	 * @brief 렌더 매니저에서 사용할 셰이더 캐시입니다.
	 */
	std::unordered_map<std::wstring, Shader*> shaderCache_;
};