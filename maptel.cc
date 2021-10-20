#include <iostream>
#include <unordered_map>
#include <locale>
#include "maptel.h"

namespace {
    using std::unordered_map;
    using std::cout, std::cerr;
    using std::string, std::to_string;

    using telnum = string;
    using dict = unordered_map<telnum, telnum>;
    using dict_id = unsigned long; // TODO: Być może uint32_t lub size_t?
    using dictmap = unordered_map<dict_id, dict>;

#ifdef NDEBUG
    constexpr auto debug{false};
#else
    constexpr auto debug{true};
#endif

    dictmap & maptel() {
        static dictmap maptel;
        return maptel;
    }
    dict_id dict_count = 0;

    void show_debug(const string &to_write) {
        if (debug)
            cerr << "maptel: " << to_write << "\n";
    }

    telnum check_and_parse_number(char const *tel) {
        assert(tel);

        for (size_t i = 0; tel[i]; i++){
            assert(isdigit(tel[i]));
            assert(i < jnp1::TEL_NUM_MAX_LEN);
        }

        telnum result{telnum(tel)};

        return result;
    }

    dict chek_and_get_dict(unsigned long id) {
        assert(maptel().count(id) == 1);

        return maptel()[id];
    }
}

namespace jnp1 {

    // Kasia
    unsigned long maptel_create(void) {
        show_debug("maptel_create()");

        dict_id id{dict_count++};
        maptel()[id] = dict();

        assert(maptel().count(id) == 1);
        show_debug("maptel_create: new map id = " + to_string(id));

        return id;
    }

    // Tima
    void maptel_delete(unsigned long id) {
        cout << "TO DO maptel delete: id=" << id << "\n";
    }

    // Kasia
    void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
        dict chosen_dict{chek_and_get_dict(id)};
        telnum str_tel_src{check_and_parse_number(tel_src)};
        telnum str_tel_dst{check_and_parse_number(tel_dst)};

        show_debug("maptel_insert(" + to_string(id) + ", " + str_tel_src + ", " + str_tel_dst + ")");

        chosen_dict[str_tel_src] = str_tel_dst;

        assert(chosen_dict.count(str_tel_src) == 1);
        assert(chosen_dict[str_tel_src] == str_tel_dst);

        show_debug("maptel_insert: inserted");
    }

    // Tima
    void maptel_erase(unsigned long id, char const *tel_src) {
        cout << "TO DO maptel erase: id=" << id << " tel_src=" << tel_src << "\n";
    }

    // Tima
    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
        cout << "TO DO maptel transform: id=" << id << " tel_src=" << tel_src << " tel_dst="
             << tel_dst << " len=" << len << "\n";
    }
}