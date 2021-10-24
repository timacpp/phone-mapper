#include <cassert>
#include <cstring>
#include <unordered_map>
#include "maptel.h"

namespace {
    using std::cerr;
    using std::string;
    using std::unordered_map;

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
        template<typename... Args>
        static void print_behaviour(const string& pref, const string& sep,
                                    const string& post, Args const&... args) {
            cerr << "maptel: " << pref;
            ((cerr << args << sep), ...);
            cerr << post;
        }

    public:
        template<typename... Args>
        static void start_session(const string& func, Args const&... args) {
            if (debug_compile) {
                print_behaviour(func + '(', ", ", ")\n", args...);
            }
        }

        template<typename... Args>
        static void end_session(const string& func, Args const&... args) {
            if (debug_compile) {
                print_behaviour(func + ": ", " ", "\n", args...);
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
            if (!std::isdigit(tel[i]))
                return false;
        }

        return true;
    }

    telnum telnum_create(char const *tel) {
        assert(telnum_validate(tel));
        return {tel};
    }
}

namespace jnp1 {
    unsigned long maptel_create(void) {
        debug::start_session(__FUNCTION__);

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

    void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
        debug::start_session(__FUNCTION__, id, tel_src, tel_dst);

        auto chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto dest{telnum_create(tel_dst)};

        assert(!chosen_dict.count(src));
        chosen_dict[src] = dest;

        assert(chosen_dict.count(src) && chosen_dict[src] == dest);
        debug::end_session(__FUNCTION__, "inserted");
    }

    void maptel_erase(unsigned long id, char const *tel_src) {
        debug::start_session(__FUNCTION__ , id, tel_src);

        auto chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto debug_res_msg{
            chosen_dict.count(src) ? "erased" : "nothing to erase"
        };

        chosen_dict.erase(src);

        assert(!chosen_dict.count(src));
        debug::end_session(__FUNCTION__, debug_res_msg);
    }

    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
    }
}