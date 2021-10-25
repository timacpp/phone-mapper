#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include "maptel.h"

namespace {
    using std::cerr, std::endl;
    using std::string, std::strcpy;
    using std::pair, std::make_pair, std::tuple;
    using std::unordered_set, std::unordered_map;
    using std::isdigit;

    using telnum = string;
    using dict_id = size_t;
    using dict = unordered_map<telnum, telnum>;
    using dictmap = unordered_map<dict_id, dict>;

    class debug {
#ifdef NDEBUG
        static constexpr auto debug_compile{false};
#else
        static constexpr auto debug_compile{true};
#endif

        using strtup = tuple<string, string, string>;

        template<typename Arg, typename... Args>
        static void print_behaviour(const strtup& format, const Arg& first,
                                    const Args&... args) {
            const auto& [prefix, separator, postfix]{format};
            ((cerr << "maptel: " << prefix << first) << ... <<
                (cerr << separator, args)) << postfix << endl;
        }

    public:
        template<typename Arg, typename... Args>
        static void start_session(const string& func, const Arg& first,
                                  const Args&... args) {
            if (debug_compile) {
                print_behaviour({func + '(', ", ", ")"}, first, args...);
            }
        }

        template<typename Arg, typename... Args>
        static void end_session(const string& func, const Arg& first,
                                const Args&... args) {
            if (debug_compile) {
                print_behaviour({func + ": ", " ", ""}, first, args...);
            }
        }

        static void print_message(const string& func, const string& msg) {
            if (debug_compile) {
                print_behaviour({func + ": ", "", ""}, msg);
            }
        }
    };
    
    dictmap& maptel() {
        static dictmap maptel;
        return maptel;
    }

    dict_id& dict_count() {
        static dict_id dict_count{0L};
        return dict_count;
    }

    dict& get_dict(unsigned long id) {
        assert(maptel().count(id));
        return maptel()[id];
    }

    bool telnum_validate(char const *tel) {
        if (!tel)
            return false;

        for (size_t i{0}; tel[i]; i++) {
            if (!isdigit(tel[i]) || i > jnp1::TEL_NUM_MAX_LEN)
                return false;
        }

        return true;
    }

    telnum telnum_create(char const *tel) {
        assert(telnum_validate(tel));
        return {tel};
    }

    pair<telnum, bool> find_last_telnum(dict& from, const telnum& src) {
        telnum last{src};
        bool cycle_exists = false;
        unordered_set<telnum> visited;

        while (from.count(last) && !cycle_exists) {
            cycle_exists |= visited.count(last);
            visited.insert(last);
            last = from[last];
        }

        if (cycle_exists)
            last = src;

        return {last, cycle_exists};
    };
}

namespace jnp1 {
    unsigned long maptel_create(void) {
        debug::start_session(__FUNCTION__, "");

        dict_id next_id{dict_count()++};
        maptel()[next_id] = dict();

        assert(maptel().count(next_id));
        debug::end_session(__FUNCTION__, "new map id =", next_id);

        return next_id;
    }

    void maptel_delete(unsigned long id) {
        debug::start_session(__FUNCTION__, id);

        assert(maptel().count(id));
        maptel().erase(id);

        assert(!maptel().count(id));
        debug::end_session(__FUNCTION__, "map", id, "deleted");
    }

    void maptel_insert(unsigned long id, char const *tel_src,char const *tel_dst) {
        auto& chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto dest{telnum_create(tel_dst)};

        debug::start_session(__FUNCTION__, id, src, dest);

        chosen_dict[src] = dest;
        assert(chosen_dict.count(src) && chosen_dict[src] == dest);

        debug::end_session(__FUNCTION__, "inserted");
    }

    void maptel_erase(unsigned long id, char const *tel_src) {
        auto& chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto debug_end_msg{
                chosen_dict.count(src) ? "erased" : "nothing to erase"
        };

        debug::start_session(__FUNCTION__ , id, tel_src);

        chosen_dict.erase(src);
        assert(!chosen_dict.count(src));

        debug::end_session(__FUNCTION__, debug_end_msg);
    }

    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
        auto& chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto& [dest, cycle_exists]{find_last_telnum(chosen_dict, src)};

        debug::start_session(__FUNCTION__, id, tel_src, (void *) tel_dst, len);

        if (cycle_exists) {
            debug::print_message(__FUNCTION__, "cycle detected");
        }

        assert(dest.size() < len);
        strcpy(tel_dst, dest.c_str());

        debug::end_session(__FUNCTION__, src, "->", tel_dst);
    }
}