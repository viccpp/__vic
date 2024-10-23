// Generic utility for sequential one by one elements reading (input)
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_CONCEPT_H
#define __VIC_SREADERS_CONCEPT_H

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Expected s-reader interface (concept)
//////////////////////////////////////////////////////////////////////////////
// template<class T>
// interface sreader
// {
//     sreader(sreader && ); or sreader(const sreader & );
//     sreader_result<T> operator()(); // throws on errors
// };
//////////////////////////////////////////////////////////////////////////////
// template<class T>
// interface sreader_result
// {
//     explicit operator bool() const; // Was the read successful (not EOF)?
//     T value() const; // The read result. Precondition: *this == true
// };
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
