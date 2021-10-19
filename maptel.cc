#include <iostream>
#include <unordered_map>
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

    dictmap maptel;

    void show_debug(const string &to_write) {
        if (debug) {
            cerr << "maptel: " << to_write << "\n";
        }
    }
}

#ifdef __cplusplus
namespace jnp1 {
#endif
// Kasia
// Tworzy słownik i zwraca liczbę naturalną będącą jego identyfikatorem.
    unsigned long maptel_create(void) {
        show_debug("maptel_create()");

        size_t id = maptel.size();
        maptel.insert({id, dict()});

        show_debug("maptel_create: new map id = " + to_string(id));

        return id;
    }

// Tima
// Usuwa słownik o identyfikatorze id.
    void maptel_delete(unsigned long id) {
        cout << "TO DO maptel delete: id=" << id << "\n";
    }

// Kasia
// Wstawia do słownika o identyfikatorze id informację o zmianie numeru
// tel_src na numer tel_dst. Nadpisuje ewentualną istniejącą informację.
// TODO sprawdzać poprawność tel_src i tel_dst
// TODO obsłużyć błędy np brak podanego słownika
    void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
        show_debug("maptel_insert(" + to_string(id) + ", " + tel_src + ", " + tel_dst + ")");

        dict chosen_dictionary = maptel.at(id);
        chosen_dictionary.insert({string(tel_src), string(tel_dst)});

        show_debug("maptel_insert: inserted");
    }

// Tima
// Jeśli w słowniku o identyfikatorze id jest informacja o zmianie numeru
// tel_src, to ją usuwa. W przeciwnym przypadku nic nie robi.
    void maptel_erase(unsigned long id, char const *tel_src) {
        cout << "TO DO maptel erase: id=" << id << " tel_src=" << tel_src << "\n";
    }

// Tima
// Sprawdza, czy w słowniku o identyfikatorze id jest zapisana zmiana numeru
// tel_src. Podąża ciągiem kolejnych zmian. Zapisuje zmieniony numer w tel_dst.
// Jeśli nie ma zmiany numeru lub zmiany tworzą cykl, to zapisuje w tel_dst
// numer tel_src. Wartość len to rozmiar przydzielonej pamięci wskazywanej
// przez tel_dst.
    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
        cout << "TO DO maptel transform: id=" << id << " tel_src=" << tel_src << " tel_dst="
             << tel_dst << " len=" << len << "\n";
    }

#ifdef __cplusplus
}
#endif

