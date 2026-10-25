#pragma once
#include "./Graphics/ICanvas.hpp"
#include "./Shapes/Picture.hpp"
#include "./CanvasView.hpp"
#include "./Graphics/Canvases/CanvasListeners/CanvasMouseListener.hpp"

class EditorWindow {
public:
	EditorWindow(shapes::Picture& picture)
		: m_canvas(std::make_unique<SFMLCanvas>(1920, 1080, "Shapes drawing"))
		, m_canvasView(picture, m_session, *m_canvas)
	{
		m_listener = std::make_unique<CanvasMouseListener>(m_canvasView.GetController());
		m_canvas->AddListener(*m_listener);
	}

	void ChangePicture(shapes::Picture& picture) {
		m_canvasView.ChangePicture(picture);
	}

	void Draw(const std::string& id) {
		m_canvasView.Draw(id);
	}

	void DrawPicture() {
		m_canvasView.DrawPicture();
	}

	void ClearCanvas() {
		m_canvas->Clear();
	}
private:
	std::unique_ptr<gfx::ICanvas> m_canvas;

	EditorSession m_session;
	CanvasView m_canvasView;
	std::unique_ptr<ICanvasListener> m_listener;
};