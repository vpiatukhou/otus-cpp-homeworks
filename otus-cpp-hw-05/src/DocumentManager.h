#pragma once

#include "Document.h"
#include "ExportFormat.h"
#include "ImportFormat.h"
#include <string>
#include <memory>

namespace Homework {

/// @brief Provides API to manage documents (CRUD, import, export etc.) and holds an already created document.
class DocumentManager {
private:
    std::shared_ptr<Document> document = nullptr;
public:
    DocumentManager() = default;

    DocumentManager(const DocumentManager&) = delete;
    DocumentManager(DocumentManager&&) = delete;

    DocumentManager operator=(DocumentManager&) = delete;
    DocumentManager operator=(DocumentManager&&) = delete;

    void createDocument(const std::string& name);
    void exportToFile(const std::string& filepath, ExportFormat format);
    void importFromFile(const std::string& filepath, ImportFormat format);

    std::shared_ptr<Document> getDocument() const;

};

};
