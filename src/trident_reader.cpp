#include "trident_reader.h"

TridentReader::TridentReader(std::string const &kb_path) {
    path_kb = "/home/mike/work/lars/trident/data/tw";
}

TridentReader::~TridentReader() { }

std::vector<std::shared_ptr<ares::util::Grounding>>
TridentReader::read_background_data(ares::util::Timeline &timeline) {
    auto result = std::vector<std::shared_ptr<ares::util::Grounding>>();
    KBConfig config;
    auto kb = std::make_unique<KB>(path_kb.c_str(), true, true, true, config);
    Querier *q = kb->query();
    int64_t const KBVAR_S = -1;
    int64_t const KBVAR_O = -2;
    nTerm predicate_id = 0;
    int len = 3;
    std::string predicate_string("<b>");
    char *predicate_key = const_cast<char *>(predicate_string.c_str());
    bool p_found = q->nodid(predicate_key, len, &predicate_id);
    EdgeItr *itr = q->edg_srd(KBVAR_S, predicate_id, KBVAR_O);
    bool keep_going = true;
    while (itr->hasNext()) {
        itr->next();
        int64_t subject_id = itr->getSubject();
        int64_t object_id = itr->getObject();
        char subject[MAX_TERM_SIZE];
        char object[MAX_TERM_SIZE];
        int subj_len = 0;
        int obj_len = 0;
        bool subj_lbl_found = q->lbl_n(subject_id, subject, subj_len);
        bool obj_lbl_found = q->lbl_n(object_id, object, obj_len);
        auto grounding = init_grounding(subject, predicate_string, object, 
                timeline);
        result.push_back(grounding);
    }
    std::cout << std::endl;
    return result;
}

std::shared_ptr<ares::util::Grounding> TridentReader::init_grounding(
        std::string subject, std::string predicate, std::string object,
        ares::util::Timeline const &timeline
        ) const {
    std::vector<std::string> constant_vector;
    constant_vector.push_back(subject);
    constant_vector.push_back(object);
    uint64_t consideration_time = timeline.get_min_time();
    uint64_t horizon_time = ares::util::Timeline::INFINITE_TIME;
    uint64_t consideration_count = 0;
    uint64_t horizon_count = ares::util::Timeline::INFINITE_TIME;
    bool is_fact = false;
    bool is_background_fact = true;
    return std::make_shared<ares::util::Grounding>(
                predicate, consideration_time, horizon_time, 
                consideration_count, horizon_count,
                is_fact, is_background_fact, constant_vector);
}

// ===== Trash ===
    //auto edge_count = q->countEdges(KBVAR_S, predicate_id, KBVAR_O);
    //if (edge_count > 0) {
    //bool keep_going = true;
    //while (keep_going) {
        //if (itr->hasNext()) {
            //itr->next();
        //} else {
            //keep_going = false;
        //}
    //}
    //} else {
        //std::cout << "No edges found!" << endl;
    //}
    //
        //std::cout << "subject_id = " << subject_id << std::endl;
        //std::cout << "object_id = " << object_id << std::endl;
        //
    //std::cout << "predicate found: " << p_found << "; predicate_id: " 
        //<< predicate_id << std::endl;
        //
//std::cout << predicate_string << "(" << subject << ", " << object << ");  ";
