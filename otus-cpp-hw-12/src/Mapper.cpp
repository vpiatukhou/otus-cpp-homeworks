#include "Mapper.h"

#include <utility>

namespace Homework {

    Mapper::Mapper(std::unique_ptr<FileReader>& fileReader_, MapFunction map_)
        : fileReader(std::move(fileReader_)), map(map_) {

        mapThread = std::make_unique<std::thread>([this]() { run(); });
    }

    void Mapper::join() {
        mapThread->join();
    }

    void Mapper::run() {
        std::string line;
        while (fileReader->hasNext()) {
            fileReader->readLine(line);
            if (!line.empty()) {
                map(line, output);
            }
        }
    }

    void Mapper::extractOutput(MappedData& output) {
        output = std::move(this->output);
    }
}
