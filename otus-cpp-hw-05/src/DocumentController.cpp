#include "DocumentController.h"
#include "ApplicationContext.h"

using namespace Homework;

DocumentController::DocumentController() {
	documentManager = ApplicationContext::getInstance().documentManager;
}

void DocumentController::onCreateDocument() {
	//the value would be read from an input field in a real application
	documentManager->createDocument("New document");
}

void DocumentController::onExportToFile() {
	//the values would be read from input fields in a real application
	documentManager->exportToFile("/home/user/document.svg", ExportFormat::SVG);
}

void DocumentController::onImportFromFile() {
	//the values would be read from input fields in a real application
	documentManager->importFromFile("/home/user/document.svg", ImportFormat::SVG);
}
