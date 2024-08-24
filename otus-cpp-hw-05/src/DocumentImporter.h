#pragma once

#include "Document.h"
#include <string>

namespace Homework {

/// @brief A base class for all document importers.
class DocumentImporter {
public:
    /// @brief Imports a document from the given file.
	/// @param document - an empty document which will be populated from the file
	/// @param filepath - the path to the file in the given format
    virtual void importFromFile(Document& document, const std::string& filepath) = 0;

    virtual ~DocumentImporter() = default;
};

};
