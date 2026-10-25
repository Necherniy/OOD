#pragma once
#include "Shapes/Shape.hpp"
#include "./IEditorSessionListener.hpp"

class EditorSession {
public:
	EditorSession() 
	{
	}

	const shapes::Shape* GetSelectedShape() const {
		return m_selectedShape;
	}

	shapes::Shape* GetSelectedShape() {
		return m_selectedShape;
	}

	void SetSelectedShape(shapes::Shape* shape) {
		m_selectedShape = shape;
		NotifyListeners();
	}

	void AddListener(IEditorSessionListener* listener) {
		auto it = FindListener(*listener);

		if (it == m_listeners.end()) {
			m_listeners.push_back(listener);
		}
	}
private:
	shapes::Shape* m_selectedShape = nullptr;
	std::vector<IEditorSessionListener*> m_listeners;

	std::vector<IEditorSessionListener*>::iterator FindListener(const IEditorSessionListener& listener) {
		return std::find(m_listeners.begin(), m_listeners.end(), &listener);
	}

	void NotifyListeners() {
		for (const auto& listener : m_listeners) {
			listener->OnSelectionChanged();
		}
	}
};