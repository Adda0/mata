// TODO: Some header.

#include <unordered_set>

#include <catch2/catch.hpp>

#include "mata/alphabet.hh"
#include "mata/nfa/nfa.hh"
#include "mata/nfa/algorithms.hh"

using namespace mata;
using namespace mata::nfa::algorithms;
using namespace mata::nfa;
using namespace mata::utils;
using namespace mata::parser;
using OnTheFlyAlphabet = mata::OnTheFlyAlphabet;

using Word = std::vector<Symbol>;

template<class T> void unused(const T &) {}

TEST_CASE("mata::OnTheFlyAlphabet::add_symbols_from()") {
    OnTheFlyAlphabet alphabet{ { "a", 4 }, { "b", 2 }, { "c", 10 } };
    auto symbols{ alphabet.get_alphabet_symbols() };
    mata::utils::OrdVector<Symbol> expected{ 4, 2, 10 };
    CHECK(symbols == expected);
    CHECK(alphabet.get_next_value() == 11);
    CHECK(alphabet.get_symbol_map() == OnTheFlyAlphabet::StringToSymbolMap{ { "a", 4 }, { "b", 2 }, { "c", 10 } });

    alphabet.add_new_symbol("e", 7);
    CHECK_THROWS_AS(alphabet.add_new_symbol("a", 0), std::runtime_error);

    symbols = alphabet.get_alphabet_symbols();
    expected = mata::utils::OrdVector<Symbol>{ 7, 4, 2, 10 };
    CHECK(symbols == expected);
    CHECK(alphabet.get_next_value() == 11);
    CHECK(alphabet.get_symbol_map() == OnTheFlyAlphabet::StringToSymbolMap {
        { "a", 4 }, { "b", 2 }, { "c", 10 }, { "e", 7 }
    });
}

TEST_CASE("mata::EnumAlphabet") {
    EnumAlphabet alphabet{};
    EnumAlphabet alphabet2{ 1, 2, 3, 4, 5 };

    CHECK(alphabet.get_alphabet_symbols().empty());
    CHECK(alphabet.get_number_of_symbols() == 0);
    CHECK(alphabet.get_next_value() == 0);
    CHECK(alphabet.is_equal(alphabet));
    CHECK(!alphabet.is_equal(alphabet2));
    CHECK(alphabet.get_complement({}).empty());

    CHECK_NOTHROW(alphabet.add_new_symbol(1));
    CHECK_NOTHROW(alphabet.add_new_symbol(1));

    CHECK(alphabet.get_alphabet_symbols() == OrdVector<Symbol>{ 1 });
    CHECK(alphabet.get_number_of_symbols() == 1);
    CHECK(alphabet.get_next_value() == 2);
    CHECK(alphabet.get_complement({}) == OrdVector<Symbol>{ 1 });

    CHECK_NOTHROW(alphabet.add_new_symbol(2));
    CHECK_NOTHROW(alphabet.add_new_symbol(3));

    CHECK(alphabet.get_alphabet_symbols() == OrdVector<Symbol>{ 1, 2, 3 });
    CHECK(alphabet.get_number_of_symbols() == 3);
    CHECK(alphabet.get_next_value() == 4);
    CHECK(alphabet.get_complement({ 2 }) == OrdVector<Symbol>{ 1, 3 });

    CHECK_NOTHROW(alphabet.add_symbols_from(alphabet2));
    CHECK(alphabet.get_alphabet_symbols() == alphabet2.get_alphabet_symbols());

    CHECK_THROWS(alphabet.translate_symb("3414"));
    CHECK(alphabet.translate_symb("1") == 1);
    CHECK_THROWS(alphabet.translate_symb("3414not a number"));
    CHECK_THROWS(alphabet.translate_symb("not a number"));
}
