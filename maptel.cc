#include <iostream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include "maptel.h"

namespace {
    using std::cerr, std::endl;
    using std::string, std::pair, std::tuple;
    using std::unordered_set, std::unordered_map;

    using telnum = string;
    using dict_id = size_t;
    using dict = unordered_map<telnum, telnum>;
    using dictmap = unordered_map<dict_id, dict>;

    class debug {
        /* Variable denoting whether NDEBUG flag is enabled. */
#ifdef NDEBUG
        static constexpr auto debug_compile{false};
#else
        static constexpr auto debug_compile{true};
#endif

        using strtup = tuple<string, string, string>;

        /* Outputs to cerr a pack of arguments with
         * selected message prefix, postfix and separator. */
        template<typename Arg, typename... Args>
        [[maybe_unused]] static void print_behaviour(const strtup &format, const Arg &first,
                                    const Args &... args) {
            const auto& [prefix, separator, postfix]{format};
            ((cerr << "maptel: " << prefix << first) << ... <<
                    (cerr << separator, args)) << postfix << endl;
        }

    public:

        /* Outputs to cerr a called function name and its parameters. */
        template<typename Arg, typename... Args>
        static void start_session(const string &func, const Arg &first,
                                  const Args &... args) {
            if constexpr (debug_compile) {
                print_behaviour({func + '(', ", ", ")"}, first, args...);
            }
        }

        /* Outputs to cerr mid-result message of a called function */
        static void print_message(const string &func, const string &msg) {
            if constexpr (debug_compile) {
                print_behaviour({func + ": ", "", ""}, msg);
            }
        }

        /* Outputs to cerr result status of a called function. */
        template<typename Arg, typename... Args>
        static void end_session(const string &func, const Arg &first,
                                const Args &... args) {
            if constexpr (debug_compile) {
                print_behaviour({func + ": ", " ", ""}, first, args...);
            }
        }
    };

    dictmap &maptel() {
        static dictmap maptel;
        return maptel;
    }

    dict_id &dict_count() {
        static dict_id dict_count{0};
        return dict_count;
    }

    dict &get_dict(unsigned long id) {
        auto found_dict{maptel().find(id)};
        assert(found_dict != maptel().end());
        return found_dict->second;
    }

    [[maybe_unused]] bool telnum_validate(char const *tel) {
        if (!tel)
            return false;

        size_t size{0};
        for (; tel[size]; size++) {
            if (!isdigit(tel[size]) || size >= jnp1::TEL_NUM_MAX_LEN)
                return false;
        }
        assert(size > 0);

        return true;
    }

    telnum telnum_create(char const *tel) {
        assert(telnum_validate(tel));
        return {tel};
    }

    /* Finds last number in history change and returns it with cycle information. */
    pair<telnum, bool> find_last_telnum(dict &history, const telnum &src) {
        telnum last{src};
        bool cycle_found = false;
        unordered_set<telnum> visited;

        for (auto last_it{history.find(src)};
             last_it != history.end() && !cycle_found;
             last_it = history.find(last_it->second)) {

            cycle_found |= (visited.find(last_it->first) != visited.end());
            visited.insert(last_it->first);
            last = (cycle_found ? src : last_it->second);
        }

        return {last, cycle_found};
    }
}

namespace jnp1 {
    unsigned long maptel_create(void) {
        debug::start_session(__FUNCTION__, "");

        dict_id next_id{dict_count()++};
        maptel()[next_id] = dict();

        assert(maptel().find(next_id) != maptel().end());
        debug::end_session(__FUNCTION__, "new map id =", next_id);

        return next_id;
    }

    void maptel_delete(unsigned long id) {
        debug::start_session(__FUNCTION__, id);

        assert(maptel().find(id) != maptel().end());
        maptel().erase(id);

        assert(maptel().find(id) == maptel().end());
        debug::end_session(__FUNCTION__, "map", id, "deleted");
    }

    void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
        auto &chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto dest{telnum_create(tel_dst)};

        debug::start_session(__FUNCTION__, id, src, dest);

        chosen_dict[src] = dest;

        [[maybe_unused]] auto found_change = chosen_dict.find(src);
        assert(found_change != chosen_dict.end() && found_change->second == dest);

        debug::end_session(__FUNCTION__, "inserted");
    }

    void maptel_erase(unsigned long id, char const *tel_src) {
        auto &chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto debug_end_msg{
            chosen_dict.find(src) != chosen_dict.end() ? "erased" : "nothing to erase"
        };

        debug::start_session(__FUNCTION__, id, tel_src);

        chosen_dict.erase(src);
        assert(chosen_dict.find(src) == chosen_dict.end());

        debug::end_session(__FUNCTION__, debug_end_msg);
    }

    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
        assert(tel_dst);
        auto &chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto &[dest, cycle_exists]{find_last_telnum(chosen_dict, src)};

        debug::start_session(__FUNCTION__, id, tel_src, (void *)tel_dst, len);

        if (cycle_exists) {
            debug::print_message(__FUNCTION__, "cycle detected");
        }

        assert(dest.size() < len);
        strcpy(tel_dst, dest.c_str());

        debug::end_session(__FUNCTION__, src, "->", tel_dst);
    }
}