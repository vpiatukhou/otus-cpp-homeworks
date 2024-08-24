#include "ToolProvider.h"
#include "Ellipse.h"
#include "Rectangle.h"

using namespace Homework;

ToolProvider::ToolProvider(const std::shared_ptr<Document>& _document) : document(_document) {
}

void ToolProvider::createEllipse() {
	//a shape is created with default settings. A user will change them later on GUI
	auto ellipse = std::make_unique<Ellipse>("New ellipse", Color(), 0);
	ellipse->setColor(Color());
	ellipse->setHalfRadiusX(1.0);
	ellipse->setHalfRadiusY(1.0);

	document->addShape(std::move(ellipse));
}

void ToolProvider::createRectangle() {
	//a shape is created with default settings. A user will change them later on GUI
	auto rectangle = std::make_unique<Rectangle>("New rectangle", Color(), 0);
	rectangle->setColor(Color());
	rectangle->setHeight(1.0);
	rectangle->setWeight(1.0);

	document->addShape(std::move(rectangle));
}

void ToolProvider::addSelectedShapeToDocument(double positionX, double positionY) {
	selectedShape->setPositionX(positionX);
	selectedShape->setPositionY(positionY);

	document->addShape(std::move(selectedShape));
	selectedShape = nullptr;
}

void ToolProvider::deleteSelectedShape() {
	document->deleteShape(selectedShape);
	selectedShape = nullptr;
}

void ToolProvider::selectShape(double positionX, double positionY) {
	selectedShape = document->selectShape(positionX, positionY);
}