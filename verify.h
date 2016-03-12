/// @file verify.h
/// @brief like assert(), but with debug off
/// @author Jeff Perry <jeffsp@gmail.com>
/// @version 1.0
/// @date 2013-01-14

#ifndef VERIFY_H
#define VERIFY_H

#include <sstream>
#include <stdexcept>

/// @brief Support for VERIFY macro
inline void VERIFY (const char *e, const char *file, unsigned line)
{
    std::stringstream s;
    s << "verification failed in " << file << ", line " << line << ": " << e;
    throw std::runtime_error (s.str ());
}

/// @brief VERIFY that a statement is true, ignoring NDEBUG
#define verify(e) (void)((e) || (VERIFY (#e, __FILE__, __LINE__), 0))

#endif // VERIFY_H
