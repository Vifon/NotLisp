// File: keyword.hpp
#ifndef _h_VFN_KEYWORD_
#define _h_VFN_KEYWORD_

#include <ostream>

namespace vfn {

/**
 * Available symbolic constants.
 */
enum class Keyword {
    // Braces
    ParenBegin,                 ///< <tt>'('</tt>
    ParenEnd,                   ///< <tt>')'</tt>
    ListBegin,                  ///< <tt>'['</tt>
    ListEnd,                    ///< <tt>']'</tt>
    BlockBegin,                 ///< <tt>'{'</tt>
    BlockEnd,                   ///< <tt>'}'</tt>

    // Keywords
    If,                         ///< <tt>if</tt>
    Else,                       ///< <tt>else</tt>
    Let,                        ///< <tt>let</tt>
    Fun,                        ///< <tt>fun</tt>
    For,                        ///< <tt>for</tt>
    In,                         ///< <tt>in</tt>
    Return,                     ///< <tt>return</tt>
    Print,                      ///< <tt>print</tt>
    Map,                        ///< <tt>map</tt>
    Filter,                     ///< <tt>filter</tt>

    // Operators
    Plus,                       ///< <tt>'+'</tt>
    Minus,                      ///< <tt>'-'</tt>
    Mult,                       ///< <tt>'*'</tt>
    Div,                        ///< <tt>'/'</tt>
    Assignment,                 ///< <tt>'='</tt>
    Equals,                     ///< <tt>'=='</tt>
    NotEquals,                  ///< <tt>'!='</tt>

    // Separators
    Comma,                      ///< <tt>','</tt>
    Semicolon,                  ///< <tt>';'</tt>
};

std::ostream& operator<<(std::ostream& out, Keyword keyword);

} // namespace vfn

#endif
