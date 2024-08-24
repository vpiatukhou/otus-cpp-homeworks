#include "DocumentExporterFactory.h"
#include "PngExporter.h"
#include "SvgExporter.h"

#include <stdexcept>

std::unique_ptr<Homework::DocumentExporter> Homework::createDocumentExporter(Homework::ExportFormat format) {
	switch (format) {
		case Homework::ExportFormat::SVG:
			return std::make_unique<SvgExporter>();
		case Homework::ExportFormat::PNG:
			return std::make_unique<PngExporter>();
		default:
			throw std::invalid_argument("Unsupported format.");
	}
}
