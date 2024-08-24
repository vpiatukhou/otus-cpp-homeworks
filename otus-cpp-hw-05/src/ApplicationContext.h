#pragma once

#include "DocumentManager.h"
#include "ToolProvider.h"
#include <memory>

namespace Homework {

/// @brief Holds application model. A singleton.
class ApplicationContext {
public:
	const std::shared_ptr<DocumentManager> documentManager = std::make_shared<DocumentManager>();

	ApplicationContext() = default;
	ApplicationContext(const ApplicationContext&) = delete;
	ApplicationContext operator=(const ApplicationContext&) = delete;

	static ApplicationContext& getInstance() {
		static ApplicationContext instance;
		return instance;
	}
};

};
