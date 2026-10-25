#pragma once

class IEditorSessionListener {
public:
	virtual ~IEditorSessionListener() = default;
	virtual void OnSelectionChanged() = 0;
};