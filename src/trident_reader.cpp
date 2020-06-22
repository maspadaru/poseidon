#include "trident_reader.h"

TridentReader::TridentReader(std::string const &stream_path) {
    source.open(stream_path);
}

TridentReader::~TridentReader() { source.close(); }

std::vector<std::shared_ptr<ares::util::Grounding>>
TridentReader::read_background_data(ares::util::Timeline &timeline) {
    return std::vector<std::shared_ptr<ares::util::Grounding>>();
}
