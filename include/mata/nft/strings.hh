/* nfa-strings.hh -- Operations on NFAs for string solving.
 */

#ifndef MATA_NFT_STRING_SOLVING_HH_
#define MATA_NFT_STRING_SOLVING_HH_

#include "mata/nfa/strings.hh"
#include "nft.hh"

namespace mata::nft::strings {
/**
 * Create identity transducer over the @p alphabet with @p level_cnt levels.
 */
Nft create_identity(mata::Alphabet* alphabet, Level level_cnt = 2);

/**
 * Create identity input/output transducer with 2 levels over the @p alphabet with @p level_cnt levels with single
 *  symbol @p from_symbol replaced with @to_symbol.
 */
Nft create_identity_with_single_replace(mata::Alphabet* alphabet, Symbol from_symbol, Symbol to_symbol);

Nft reluctant_replace(
    const std::string& regex,
    const std::string& replacement,
    Alphabet* alphabet,
    // TODO: Change into constants?
    Symbol begin_marker = EPSILON - 101,
    Symbol end_marker = EPSILON - 100
);
Nft reluctant_replace(
    mata::nfa::Nfa regex,
    const std::string& replacement,
    Alphabet* alphabet,
    Symbol begin_marker = EPSILON - 101,
    Symbol end_marker = EPSILON - 100
);

nfa::Nfa end_marker_dfa(nfa::Nfa regex);
Nft marker_dft(const nfa::Nfa& marker_dfa, Symbol marker);

nfa::Nfa generic_end_marker_dfa(const std::string& regex, Alphabet* alphabet);
nfa::Nfa generic_end_marker_dfa(nfa::Nfa regex, Alphabet* alphabet);
} // Namespace mata::nft::strings.

#endif // MATA_NFT_STRING_SOLVING_HH_.
