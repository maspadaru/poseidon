#include "simple_reader.h"

SimpleReader::SimpleReader(std::string const &stream_path)
    : stream_path(stream_path) {}

bool SimpleReader::has_metadata() const { return has_metadata_m; }

bool SimpleReader::fetch_metadata() {
    // if (!has_metadata_m) {
    // std::string nothing;
    // source >> start_time;
    // source >> end_time;
    // std::getline(source, nothing, '\n');
    // has_metadata_m = true;
    //}
    return has_metadata_m;
}

uint64_t SimpleReader::get_stream_start_time() const {
    return this->start_time;
}

uint64_t SimpleReader::get_stream_end_time() const { return this->end_time; }

std::vector<std::string> SimpleReader::read_all_data() {
    std::ifstream source;
    source.open(stream_path);
    std::vector<std::string> fact_vector;
    bool keep_going = true;
    while (keep_going) {
        std::string line;
        std::getline(source, line);
        if (line.length() > 0) {
            fact_vector.push_back(line);
        }
        keep_going = source.good();
    }
    source.close();
    return fact_vector;
}

std::vector<std::string>
SimpleReader::read_next_data(uint64_t request_time_point) {
    std::cout << "SimpleReader:" << request_time_point <<  
        " >> attempting to read pipe" << std::endl;
    std::ifstream source;
    std::vector<std::string> fact_vector;
    source.open(stream_path);
    bool keep_going = true;
    while (keep_going) {
        std::string line;
        std::getline(source, line);
        if (line.length() == 0) {
            keep_going = false;
        } else {
            std::cout << "SimpleReader:" << request_time_point <<  
                " >> read line: " << line << std::endl;
            fact_vector.push_back(line);
        }
    }
    std::cout << "SimpleReader:" << request_time_point <<  
        " >> done reading pipe" << std::endl;
    return fact_vector;
    source.close();
}
