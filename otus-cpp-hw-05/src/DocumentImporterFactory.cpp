#include "DocumentImporterFactory.h"
#include "SvgImporter.h"

#include <stdexcept>

std::unique_ptr<Homework::DocumentImporter> Homework::createDocumentImporter(ImportFormat format) {
	switch (format) {
		case ImportFormat::SVG:
			return std::make_unique<SvgImporter>();
		default:
			throw std::invalid_argument("Unsupported format.");
	}
}