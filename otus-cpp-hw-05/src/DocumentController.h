#pragma once

#include "DocumentManager.h"
#include <memory>

namespace Homework {

/// @brief A controller which processes events from the Document Menu on GUI.
///		   It is a fake controller which is used to show how MCV works. 
///        The implementation of the controller depends on the used GUI framework.
class DocumentController {
private:
	std::shared_ptr<DocumentManager> documentManager;
public:
	DocumentController();

	//The methods below are event listener which may handle e.g. Qt signals.
	void onCreateDocument();
	void onExportToFile();
	void onImportFromFile();
};

};

