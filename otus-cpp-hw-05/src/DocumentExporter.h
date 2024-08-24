#pragma once

#include "Document.h"
#include <string>

namespace Homework {

/// @brief A base class for all document exporters.
class DocumentExporter {
public:
    virtual void exportToFile(const Document& document, const std::string& filepath) = 0;

    virtual ~DocumentExporter() = default;
};

};
