#pragma once
#include "./Graphics/DrawingRenderer.hpp"
#include "./CanvasController.hpp"
#include "./Shapes/PictureListeners/IPictureListener.hpp"
#include "./IEditorSessionListener.hpp"

class CanvasView : public IPictureListener, public IEditorSessionListener {
public:
	CanvasView(shapes::Picture& picture, 
		EditorSession& session, 
		gfx::ICanvas& canvas) 
		: m_picture(&picture)
		, m_session(session)
		, m_controller(&picture, session)
		, m_renderer(canvas)
	{
		m_picture->AddListener(this);
		m_session.AddListener(this);
	}

	~CanvasView() {
		m_picture->RemoveListener(*this);
	}

	void ChangePicture(shapes::Picture& picture) {
		m_picture->RemoveListener(*this);
		m_picture = &picture;
		m_picture->AddListener(this);
		m_controller.ChangePicture(picture);
		m_session.SetSelectedShape(nullptr);
	}

	void Draw(const std::string& id) {
		m_renderer.Draw(m_picture->GetShape(id));
	}

	void DrawPicture() {
		m_renderer.Clear();
		const auto& shapes = m_picture->GetShapes();
		for (const auto& entry : shapes) {
			m_renderer.Draw(*entry.shape);
		}
	}

	void OnPictureChanged() override {
		DrawPicture();

		auto* selectedShape = m_session.GetSelectedShape();
		if (selectedShape) {
			m_renderer.DrawSelectionFrame(*selectedShape);
		}
	}

	void OnSelectionChanged() override {
		DrawPicture();

		auto* selectedShape = m_session.GetSelectedShape();
		if (selectedShape) {
			m_renderer.DrawSelectionFrame(*selectedShape);
		}
	}

	void Refresh() {
		DrawPicture();

		auto* selectedShape = m_session.GetSelectedShape();
		if (selectedShape) {
			m_renderer.DrawSelectionFrame(*selectedShape);
		}
	}

	CanvasController& GetController() {
		return m_controller;
	}
private:
	shapes::Picture* m_picture;
	EditorSession& m_session;

	CanvasController m_controller;
	DrawingRenderer m_renderer;
};