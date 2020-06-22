#ifndef POSEIDON_TRIDENT_READER_H
#define POSEIDON_TRIDENT_READER_H

#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <core/io_manager.h>
#include <util/grounding.h>
#include <util/timeline.h>
#include <util/read_exception.h>
#include <util/format_exception.h>


class TridentReader {
private:
    std::string kb_path;
    //-----
    bool has_source = false;
    uint64_t start_time;
    uint64_t end_time;
    bool has_metadata_m = false;
    std::ifstream source;

public:
    TridentReader(std::string const &stream_path);
    ~TridentReader();

    std::vector<std::shared_ptr<ares::util::Grounding>>
     read_background_data(ares::util::Timeline &timeline);

};


#endif // POSEIDON_TRIDENT_READER_H
