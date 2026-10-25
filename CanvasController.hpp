#pragma once
#include "./Shapes/Picture.hpp"
#include "./EditorSession.hpp"

class CanvasController {
public:
	explicit CanvasController(shapes::Picture* picture, EditorSession& session)
		: m_picture(picture)
		, m_session(session)
	{}

	void ChangePicture(shapes::Picture& picture) {
		m_picture = &picture;
	}

	void OnMousePressed(Point point) {
		auto shape = m_picture->FindShapeAt(point);
		m_session.SetSelectedShape(shape);
		if (shape) {
			m_isDragging = true;
			m_lastMousePosition = point;
		}
	}

	void OnMouseMoved(Point point) {
		if (m_isDragging && m_session.GetSelectedShape()) {
			auto moveCoords = point - m_lastMousePosition;
			m_session.GetSelectedShape()->Move(moveCoords.m_x, moveCoords.m_y);
			m_lastMousePosition = point;
		}
	}

	void OnMouseRelased(Point point) {
		m_isDragging = false;
	}
private:
	shapes::Picture* m_picture;

	EditorSession& m_session;
	bool m_isDragging = false;
	Point m_lastMousePosition;
};