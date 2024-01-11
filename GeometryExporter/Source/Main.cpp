#include "IApplication.h"


/**
 * @brief Geometry 생성 툴 애플리케이션입니다.
 */
class GeometryExporterApp : public IApplication
{
public:
	/**
	 * @brief 생성 툴 애플리케이션의 디폴트 생성자입니다.
	 */
	GeometryExporterApp() = default;


	/**
	 * @brief 생성 툴 애플리케이션의 가상 소멸자입니다.
	 */
	virtual ~GeometryExporterApp()
	{
		Shutdown();
	}


	/**
	 * @brief 생성 툴 애플리케이션의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryExporterApp);


	/**
	 * @brief 생성 툴 프레임워크를 초기화합니다.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		toolPath_ = rootPath_ + L"GeometryExporter/";
	}


	/**
	 * @brief 생성 툴 프레임워크 사용을 종료합니다.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief 생성 툴 프레임워크를 실행합니다.
	 */
	virtual void Run() override
	{
		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief 툴 경로입니다.
	 */
	std::wstring toolPath_;


	/**
	 * @brief 타이머입니다.
	 */
	GameTimer timer_;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> app = std::make_unique<GeometryExporterApp>();
	app->Setup();
	app->Run();
	app->Shutdown();
	return 0;
}