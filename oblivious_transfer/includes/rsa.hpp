#ifndef _RSA_HPP_
#define _RSA_HPP_

#include <cmath>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

using std::string;
using std::vector;

class rsa 
{
    typedef vector<size_t>    vct;

    private:
        size_t    e;
        size_t    d;
        size_t    n;

    public:
        /* Constructors and Destructor */

        rsa(size_t p, size_t q);

        rsa(const rsa& src);
        rsa&    operator=(const rsa& src);

        ~rsa();

        /* Public Interface Functions */

        vct         encrypt(const string& message);
        string      decrypt(const vct& cipher);

        vct         get_public_key();

    private:
        /* Private Util Functions */

        bool        is_prime(size_t n);
        size_t      gcd(size_t a, size_t b);
        size_t      mod_inverse(size_t a, size_t m);
        size_t      mod_pow(size_t base, size_t exponent, size_t modulus);
};

#endif
