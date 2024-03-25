#pragma once

#include <vector>

#include "IEdit.h"

class CompoundEdit : public IEdit {
private:
	std::vector<std::shared_ptr<IEdit>> edits;

public:
	CompoundEdit() {}
	~CompoundEdit() {}

	void AddEdit(std::shared_ptr<IEdit> edit) {
		edits.push_back(edit);
	}

	virtual void Execute() override {
		for (auto& edit : edits) {
			edit->Execute();
		}
	}

	virtual void Undo() override {
		for (auto& edit : edits) {
			edit->Undo();
		}
	}

	virtual void Redo() override {
		for (auto& edit : edits) {
			edit->Redo();
		}
	}
};