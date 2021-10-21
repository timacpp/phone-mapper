#include <cassert>
#include <cstring>
#include <unordered_map>
#include "maptel.h"

namespace {
    using std::cerr;
    using std::string;
    using std::unordered_map;

    using telnum = string;
    using dict = unordered_map<telnum, telnum>;
    using dict_id = size_t; // TODO: Być może uint32_t lub size_t?
    using dictmap = unordered_map<dict_id, dict>;

#ifdef NDEBUG
    constexpr auto debug{false};
#else
    constexpr auto debug{true};
#endif

    dictmap& maptel() {
        static dictmap maptel;
        return maptel;
    }

    dict_id& dict_count() {
        static dict_id dict_count{0L};
        return dict_count;
    }

    template<typename... Args>
    void show_debug(const Args&... out) {
        if (debug) {
            cerr << "maptel: ";
            (cerr << ... << out) << "\n";
        }
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

    dict get_dict(unsigned long id) {
        assert(maptel().count(id));
        return maptel()[id];
    }
}

namespace jnp1 {
    unsigned long maptel_create(void) {
        show_debug(__FUNCTION__, "()");

        dict_id next_id{dict_count()++};
        maptel()[next_id] = dict();

        assert(maptel().count(next_id));
        show_debug(__FUNCTION__, "new map next_id = ", next_id);

        return next_id;
    }

    void maptel_delete(unsigned long id) {

    }

    void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
        dict chosen_dict{get_dict(id)};
        const auto src{telnum_create(tel_src)};
        const auto dest{telnum_create(tel_dst)};

        show_debug(__FUNCTION__, '(', id, ", ", src, ", ", dest, ')');

        chosen_dict[src] = dest;

        assert(chosen_dict.count(src) && chosen_dict[src] == dest);

        show_debug(__FUNCTION__,  " inserted");
    }

    void maptel_erase(unsigned long id, char const *tel_src) {

    }

    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {

    }
}