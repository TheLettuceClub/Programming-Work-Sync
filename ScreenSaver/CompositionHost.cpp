#include "pch.h"
#include "CompositionHost.h"

using namespace winrt;
using namespace Windows::System;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Composition::Desktop;
using namespace Windows::Foundation::Numerics;
using timeSpan = std::chrono::duration<int, std::ratio<1, 1>>;
std::chrono::seconds duration(2);
std::chrono::seconds delay(3);

CompositionHost::~CompositionHost()
{
}

CompositionHost::CompositionHost()
{
}

CompositionHost* CompositionHost::GetInstance()
{
	static CompositionHost instance;
	return &instance;
}

void CompositionHost::Initialize(HWND hwnd)
{
	EnsureDispatcherQueue();
	if (m_dispatcherQueueController) m_compositor = Compositor();
	if (m_compositor) {
		CreateDesktopWindowTarget(hwnd);
		CreateCompositionRoot();
	}
}

void CompositionHost::AddSquareElement(float size, float x, float y)
{
	auto element = m_compositor.CreateSpriteVisual();
	uint8_t r = (double)(double)(rand() % 255);
	uint8_t g = (double)(double)(rand() % 255);
	uint8_t b = (double)(double)(rand() % 255);
	element.Brush(m_compositor.CreateColorBrush({ 255, r,g,b }));
	element.Size({ size, size });
	element.Offset({ x,y,0.0f });
	auto animation = m_compositor.CreateVector3KeyFrameAnimation();
	auto bottom = (float)600 - element.Size().y;
	animation.InsertKeyFrame(1, { element.Offset().x, bottom, 0 });
	animation.Duration(timeSpan(duration));
	animation.DelayTime(timeSpan(delay));
	element.StartAnimation(L"Offset", animation);
	m_target.Root().as<ContainerVisual>().Children().InsertAtTop(element);
	OutputDebugString(L"Added Square element\r\n");
}

//completely fucked in that it doesn't actually display anything
void CompositionHost::AddCircleElement(float size, float x, float y)
{
	// Create a new ShapeVisual that will contain our drawings.
	ShapeVisual shape = m_compositor.CreateShapeVisual();
	shape.Size({ size,size });
	uint8_t r = (double)(double)(rand() % 255);
	uint8_t g = (double)(double)(rand() % 255);
	uint8_t b = (double)(double)(rand() % 255);

	// Create a circle geometry and set its radius.
	auto circleGeometry = m_compositor.CreateEllipseGeometry();
	circleGeometry.Radius({ 30.0f, 30.0f });

	// Create a shape object from the geometry and give it a color and offset.
	auto circleShape = m_compositor.CreateSpriteShape(circleGeometry);
	circleShape.FillBrush(m_compositor.CreateColorBrush({ 255, r,g,b }));
	circleShape.Offset({ x,y });

	// Add the circle to our shape visual.
	shape.Shapes().Append(circleShape);

	auto animation = m_compositor.CreateVector3KeyFrameAnimation();
	auto bottom = (float)600 - shape.Size().y;
	animation.InsertKeyFrame(1, { shape.Offset().x, bottom, 0 });
	animation.Duration(timeSpan(duration));
	animation.DelayTime(timeSpan(delay));
	shape.StartAnimation(L"Offset", animation);

	// Add to the visual tree.
	m_target.Root().as<ContainerVisual>().Children().InsertAtTop(shape);
	OutputDebugString(L"Added circle element\r\n");
}

//would like to add more element types if possible
void CompositionHost::AddElement(int type, float size, float x, float y)
{
	if (m_target.Root()) {
		switch (type) {
		case 1:
			AddCircleElement(size, x, y);
			break;

		case 2:
			AddSquareElement(size, x, y);
			break;
		}
	}
}

void CompositionHost::ClearScreen()
{
	auto visuals = m_target.Root().as<ContainerVisual>().Children();
	visuals.RemoveAll();
	OutputDebugString(L"Cleared screen\r\n");
}

void CompositionHost::EnsureDispatcherQueue()
{
	namespace abi = ABI::Windows::System;
	if (m_dispatcherQueueController == nullptr) {
		DispatcherQueueOptions opts{
			sizeof(DispatcherQueueOptions),
			DQTYPE_THREAD_CURRENT,
			DQTAT_COM_ASTA
		};
		Windows::System::DispatcherQueueController controller{ nullptr };
		check_hresult(CreateDispatcherQueueController(opts, reinterpret_cast<abi::IDispatcherQueueController**> (put_abi(controller))));
		m_dispatcherQueueController = controller;
	}
}

void CompositionHost::CreateDesktopWindowTarget(HWND window)
{
	namespace abi = ABI::Windows::UI::Composition::Desktop;
	auto interop = m_compositor.as<abi::ICompositorDesktopInterop>();
	DesktopWindowTarget target{ nullptr };
	check_hresult(interop->CreateDesktopWindowTarget(window, false, reinterpret_cast<abi::IDesktopWindowTarget**>(put_abi(target))));
	m_target = target;
}

void CompositionHost::CreateCompositionRoot()
{
	m_root = m_compositor.CreateSpriteVisual();
	m_root.RelativeSizeAdjustment({ 1.0f, 1.0f });
	m_root.Offset({ 0,0,0 });
	m_root.Brush(m_compositor.CreateColorBrush({ 255, 0,0,0 }));
	m_target.Root(m_root);
}
