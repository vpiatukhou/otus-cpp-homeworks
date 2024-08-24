#pragma once

#include "DocumentExporter.h"
#include "ExportFormat.h"

#include <memory>

namespace Homework {

	/// @brief Creates an instance of DocumentExporter for the given format.
	/// @param format a format, the document must be exported to
	/// @return an instance of the DocumentExporter
	std::unique_ptr<DocumentExporter> createDocumentExporter(ExportFormat format);

};
