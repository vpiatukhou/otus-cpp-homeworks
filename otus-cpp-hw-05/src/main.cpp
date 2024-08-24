#include "DocumentController.h"
#include "ToolController.h"

using namespace Homework;

int main() {
	DocumentController documentController;
	documentController.onCreateDocument();

	ToolController toolController;
	toolController.onCreateRectangle();
	toolController.onCreateEllipse();
	toolController.onSelectShape();
	toolController.onDeleteSelectedShape();

	documentController.onExportToFile();
	documentController.onImportFromFile();

	return 0;
}
