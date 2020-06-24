#ifndef POSEIDON_SIMPLE_IO_MANAGER_H
#define POSEIDON_SIMPLE_IO_MANAGER_H

#include <memory>
#include <utility>
#include <vector>

#include <core/io_manager.h>
#include <util/grounding.h>
#include <util/timeline.h>

#include "simple_parser.h"
#include "simple_reader.h"
#include "simple_writer.h"
#include "trident_reader.h"

class SimpleIOManager : public ares::core::IOManager {
  private:
    SimpleWriter simple_writer;
    SimpleReader simple_reader;
    SimpleParser simple_parser;
    TridentReader trident_reader;
    std::string latest_output;
    bool is_output_enabled;

  public:
    explicit SimpleIOManager(std::string const &stream_path,
                             std::string const &kb_path,
                             std::string const &output_path,
                             bool is_output_enabled,
                             std::vector<std::string> const &predicate_vector);

    ~SimpleIOManager() override = default;

    uint64_t read_stream_start_time() override;

    uint64_t read_stream_end_time() override;

    std::vector<std::shared_ptr<ares::util::Grounding>>
    read_stream_data(ares::util::Timeline &timeline) override;

    std::vector<std::shared_ptr<ares::util::Grounding>>
    read_background_data(ares::util::Timeline &timeline) override;

    void write_output_data(uint64_t time,
                           std::vector<std::shared_ptr<ares::util::Grounding>>
                               output_vector) override;
};

#endif // POSEIDON_SIMPLE_IO_MANAGER_H
