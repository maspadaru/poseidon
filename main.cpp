#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include <core/reasoner.h>
#include <rule/rule_parser.h>
#include <util/chase_algorithm.h>

#include "simple_io_manager.h"

std::string read_program(std::string const &program_path) {
    std::string result;
    std::ifstream f(program_path);
    if (f) {
        std::ostringstream ss;
        ss << f.rdbuf();
        result = ss.str();
    }
    return result;
}

std::vector<std::string> get_predicate_vector(
    std::vector<std::unique_ptr<ares::rule::Rule>> const &rule_vector) {
    std::set<std::string> pred_set;
    for (auto const &rule : rule_vector) {
        auto body_pred = rule->get_body_predicates();
        auto head_pred = rule->get_head_predicates();
        pred_set.insert(body_pred.begin(), body_pred.end());
    }
    std::vector<std::string> result_vector;
    std::copy(pred_set.begin(), pred_set.end(),
              std::back_inserter(result_vector));
    return result_vector;
}

void run(ares::util::ChaseAlgorithm chase_algorithm,
         std::string const &stream_path, std::string const &kb_path,
         std::string const &output_path, bool is_output_enabled,
         std::string const &rules) {
    ares::util::Settings::get_instance().set_chase_algorithm(chase_algorithm);
    auto rule_parser = ares::rule::RuleParser(rules);
    auto rule_vector = rule_parser.get_rules();
    auto pred_vector = get_predicate_vector(rule_vector);
    auto simple_io_manager =
        SimpleIOManager(stream_path, kb_path, output_path, is_output_enabled, 
                pred_vector);
    auto reasoner = ares::core::Reasoner(rule_vector, &simple_io_manager);
    auto clock_start = std::chrono::high_resolution_clock::now();
    reasoner.start();
    auto clock_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> clock_elapsed =
        clock_end - clock_start;
    auto total_facts = reasoner.get_total_facts_read();
    auto total_conclusions = reasoner.get_total_conclusions();
    double total_ms = clock_elapsed.count();
    double throughput = (total_facts * 1.0) / (total_ms / 1000);
    auto runtimes = reasoner.get_runtimes();
    double min_time = std::numeric_limits<double>::max();
    double max_time = 0;
    int min_i = 0;
    int max_i = 0;
    int i = 0;
    for (auto time : runtimes) {
        if (time < min_time) {
            min_time = time;
            min_i = i;
        }
        if (time > max_time) {
            max_time = time;
            max_i = i;
        }
        i++;
    }
    std::cout << "Facts: " << total_facts
              << ", Conclusions: " << total_conclusions << std::endl;
    std::cout << "Time: " << total_ms / 1000 << " seconds" << std::endl;
    // std::cout << "Min Time: " << min_time << " seconds; "
    //<< "timepoint = " << min_i << std::endl;
    // std::cout << "Max Time: " << max_time << " seconds; "
    //<< "timepoint = " << max_i << std::endl;
    std::cout << "Throughput: " << throughput << " facts / second "
              << std::endl;
    std::cout << "************************************************************"
              << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cerr << "Usage: poseidon PROGRAM_PATH "
                     "INPUT_PATH TRIDENT_KB_PATH [OUTPUT_PATH]  "
                  << std::endl;
        return 1;
    }
    std::string program_path(argv[1]);
    std::string stream_path(argv[2]);
    std::string kb_path(argv[3]);
    std::string output_path;
    bool is_output_enabled = false;
    if (argc == 5) {
        output_path = argv[4];
        is_output_enabled = true;
    }
    auto chase_algorithm = ares::util::ChaseAlgorithm::RESTRICTED;
    std::string const &rules = read_program(program_path);

    std::cout << "argc: " << argc << std::endl;
    std::cout << "Program: " << program_path << std::endl;
    std::cout << "Input: " << stream_path << std::endl;
    std::cout << "KB: " << kb_path << std::endl;
    std::cout << "output: " << output_path << std::endl;

    run(chase_algorithm, stream_path, kb_path, output_path, is_output_enabled,
        rules);
}
