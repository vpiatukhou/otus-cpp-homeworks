#include "DocumentManager.h"
#include "DocumentExporterFactory.h"
#include "DocumentImporterFactory.h"

using namespace Homework;

void DocumentManager::createDocument(const std::string& name) {
    document = std::make_shared<Document>();
    document->setName(name);
}

std::shared_ptr<Document> DocumentManager::getDocument() const {
    return document;
}

void DocumentManager::exportToFile(const std::string& filepath, ExportFormat format) {
    createDocumentExporter(format)->exportToFile(*document, filepath);
}

void DocumentManager::importFromFile(const std::string& filepath, ImportFormat format) {
    document = std::make_shared<Document>();
    createDocumentImporter(format)->importFromFile(*document, filepath);
}