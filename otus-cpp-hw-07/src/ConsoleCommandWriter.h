#pragma once

#include "BaseCommandWriter.h"

namespace Homework {

class ConsoleCommandWriter : public BaseCommandWriter {
public:
    void onFlush(const std::vector<std::string>& commands) override;
};

};
