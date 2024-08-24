#pragma once

#include "DocumentImporter.h"
#include "ImportFormat.h"

namespace Homework {

	/// @brief Creates an instance of DocumentImporter for the given format.
	/// @param format a format, the document must be imported from
	/// @return an instance of the DocumentImporter
	std::unique_ptr<DocumentImporter> createDocumentImporter(ImportFormat format);

};
