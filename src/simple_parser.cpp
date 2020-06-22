#include "simple_parser.h"

std::shared_ptr<ares::util::Grounding>
SimpleParser::parse_string(ares::util::Timeline const &timeline,
                         std::string const &input) {
    std::vector<std::string> token_list;
    std::string token;
    std::string predicate;
    std::stringstream iss(input);
    iss >> predicate;
    while (iss >> token) {
        token_list.push_back(token);
    }
    uint64_t time = timeline.get_time();
    uint64_t max_tuple_counter = ares::util::Timeline::INFINITE_TIME;
    current_tuple_counter++;
    auto grounding = std::make_shared<ares::util::Grounding>(
        predicate, time, time, current_tuple_counter,
        max_tuple_counter, true, false, token_list);
    return grounding;
}


std::vector<std::shared_ptr<ares::util::Grounding>>
SimpleParser::parse_data(ares::util::Timeline &timeline,
                         std::vector<std::string> const &raw_data_vector) {
    std::vector<std::shared_ptr<ares::util::Grounding>> result;
    for (const auto &raw_string : raw_data_vector) {
        if (raw_string.size() > 0) {
            auto fact = parse_string(timeline, raw_string);
            result.push_back(std::move(fact));
        }
    }
    timeline.set_tuple_count(current_tuple_counter);
    return result;
}
