#include "ToolController.h"
#include "ApplicationContext.h"

using namespace Homework;

ToolController::ToolController() {
	toolProvider = std::make_unique<ToolProvider>(ApplicationContext::getInstance().documentManager->getDocument());
}

void ToolController::onCreateRectangle() {
	toolProvider->createRectangle();
}

void ToolController::onCreateEllipse() {
	toolProvider->createEllipse();
}

void ToolController::addSelectedShapeToDocument() {
	//a position of the mouse cursor in the document
	double positonX = 50;
	double positonY = 50;
	toolProvider->addSelectedShapeToDocument(positonX, positonY);
}

void ToolController::onSelectShape() {
	//a position of the mouse cursor in the document
	double positonX = 50;
	double positonY = 50;
	toolProvider->selectShape(positonX, positonY);
}

void ToolController::onDeleteSelectedShape() {
	toolProvider->deleteSelectedShape();
}