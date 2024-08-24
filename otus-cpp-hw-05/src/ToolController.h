#pragma once

#include "ToolProvider.h"
#include <memory>

namespace Homework {

	/// @brief A controller which processes events from the Tool panel on GUI.
	///	       It is a fake controller which is used to show how MCV works. 
	///        The implementation of the controller depends on the used GUI framework.
class ToolController {
private:
	std::unique_ptr<ToolProvider> toolProvider;

public:
	ToolController();

	void onCreateRectangle();
	void onCreateEllipse();
	void addSelectedShapeToDocument();
	void onSelectShape();
	void onDeleteSelectedShape();
};

};

