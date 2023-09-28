/**
 * Benchmark: Bool_comb (b-param)
 *
 * The benchmark program reproduces the results of CADE'23 for benchmarks in directory /nfa-bench/benchmarks/bool_comb/cox
 *
 * Optimal Inputs: inputs/bench-double-bool-comb-cox.in
 *
 * NOTE: Input automata, that are of type `NFA-bits` are mintermized!
 *  - If you want to skip mintermization, set the variable `MINTERMIZE_AUTOMATA` below to `false`
 */

#include "utils/utils.hh"

constexpr bool MINTERMIZE_AUTOMATA{ true};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Input files missing\n";
        return EXIT_FAILURE;
    }

    std::vector<std::string> filenames {argv[1], argv[2]};
    std::vector<Nfa> automata;
    mata::OnTheFlyAlphabet alphabet;
    if (load_automata(filenames, automata, alphabet, MINTERMIZE_AUTOMATA) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    // This might be less-efficient, but more readable.
    Nfa lhs = automata[0];
    Nfa rhs = automata[1];


    // Setting precision of the times to fixed points and 4 decimal places

    TIME_BEGIN(intersection);
    Nfa intersect_aut = intersection(rhs, rhs);
    TIME_END(intersection);
    TIME_BEGIN(uni);
    Nfa uni_aut = uni(intersect_aut,intersect_aut);
    TIME_BEGIN(is_lang_empty1);
    uni_aut.is_lang_empty();
    TIME_END(is_lang_empty1);
    TIME_BEGIN(is_lang_empty2);
    uni_aut.is_lang_empty();
    TIME_END(is_lang_empty2);
    TIME_BEGIN(get_useful_states1);
    uni_aut.get_useful_states();
    TIME_END(get_useful_states1);
    TIME_BEGIN(get_useful_states2);
    uni_aut.get_useful_states();
    TIME_END(get_useful_states2);
    //intersect_aut.final.clear();
    TIME_BEGIN(trim);
    uni_aut.trim();
    TIME_END(trim);
    std::cout<<"trimmed states: "<<intersect_aut.num_of_states()<<std::endl;

    return EXIT_SUCCESS;
}
