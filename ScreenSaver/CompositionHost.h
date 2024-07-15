#pragma once

class CompositionHost
{
private:
	CompositionHost();
	void EnsureDispatcherQueue();
	void CreateDesktopWindowTarget(HWND);
	void CreateCompositionRoot();
	winrt::Windows::UI::Composition::Compositor m_compositor{ nullptr };
	winrt::Windows::System::DispatcherQueueController m_dispatcherQueueController{ nullptr };
	winrt::Windows::UI::Composition::Desktop::DesktopWindowTarget m_target{ nullptr };
	winrt::Windows::UI::Composition::SpriteVisual m_root{ nullptr };

public:
	~CompositionHost();
	static CompositionHost* GetInstance();
	void Initialize(HWND);
	void AddSquareElement(float, float, float);
	void AddCircleElement(float, float, float);
	void AddElement(int, float, float, float);
	void ClearScreen();
};

