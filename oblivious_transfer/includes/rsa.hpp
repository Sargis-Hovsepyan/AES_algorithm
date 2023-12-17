#ifndef _RSA_HPP_
#define _RSA_HPP_

#include <cmath>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

using std::string;
using std::vector;

class RSA 
{
    typedef vector<long long>    vct;

    private:
        long long    e;
        long long    d;
        long long    n;

    public:
        /* Constructors and Destructor */

        RSA();

        RSA(const RSA& src);
        RSA&    operator=(const RSA& src);

        ~RSA();

        /* Public Interface Functions */

        vct         encrypt(const vct& message);
        vct         decrypt(const vct& cipher);

        vct         get_public_key();

    private:
        /* Private Util Functions */

        bool        is_prime(long long n);
        bool        miller_rabin_prime(long long n);
        long long   gcd(long long a, long long b);

        
        long long   mod(long long a, long long m);
        long long   mod_inverse(long long a, long long m);
        long long   mod_pow(long long base, long long exponent, long long modulus);
};

#endif
