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

#include <trident/kb/kbconfig.h>
#include <trident/kb/kb.h>
#include <trident/kb/querier.h>

#include <core/io_manager.h>
#include <util/grounding.h>
#include <util/timeline.h>
#include <util/read_exception.h>
#include <util/format_exception.h>


class TridentReader {
private:
    std::string path_kb;

    std::shared_ptr<ares::util::Grounding> init_grounding(
        std::string subject, std::string predicate, std::string object,
        ares::util::Timeline const &timeline
        ) const; 


public:
    explicit TridentReader(std::string const &kb_path);
    ~TridentReader();

    std::vector<std::shared_ptr<ares::util::Grounding>>
     read_background_data(ares::util::Timeline &timeline);

};


#endif // POSEIDON_TRIDENT_READER_H
