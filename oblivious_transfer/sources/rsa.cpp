#include "rsa.hpp"

/* Constructors and Destructor */

RSA::RSA(size_t p, size_t q)
{
    if (!is_prime(p) || !is_prime(q))
        throw std::invalid_argument("The numbers p and q must be prime!");

    size_t phi;
    
    this->n = p * q;
    phi = (p - 1) * (q - 1);

    size_t tmp = 2;
    while (tmp < phi && gcd(tmp, phi) != 1)
        tmp++;

    this->e = tmp;
    this->d = mod_inverse(this->e, phi);
}

RSA::RSA(const RSA& src)
{
    *this = src;
}

RSA&    RSA::operator=(const RSA& src)
{
    this->e = src.e;
    this->d = src.d;
    this->n = src.n;

    return (*this);
}

RSA::~RSA() {}


/* Public Interface Functions */

typename RSA::vct   RSA::encrypt(const vct& message)
{
    vector<size_t>    encrypted;

    for (size_t c : message)
    {
        size_t cipher = mod_pow(c, this->e, this->n);
        encrypted.push_back(cipher);
    }

    return encrypted;
}

typename RSA::vct   RSA::decrypt(const vct& cipher)
{
    vector<size_t>  decrypted;

    for (size_t c : cipher)
        decrypted.push_back(mod_pow(c, this->d, this->n));

    return decrypted;
}

typename RSA::vct   RSA::get_public_key()
{
    vector<size_t>    key;

    key.push_back(e);
    key.push_back(n);

    return key;
}

/* Private Util Functions */

bool                RSA::is_prime(size_t n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(n); i += 2)
        if (n % i == 0) return false;

    return true;
}

size_t             RSA::gcd(size_t a, size_t b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

size_t             RSA::mod_inverse(size_t a, size_t m)
{
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1) return 0;

    while (a > 1)
    {
        long long q = a / m;
        long long t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m;
        a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0) x += m0;

    return x;
}


size_t            RSA::mod_pow(size_t base, size_t exponent, size_t modulus) 
{
    base %= modulus;
    size_t result = 1;

    while (exponent > 0)
    {
        if (exponent & 1) 
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent >>= 1;
    }

    return result;
}
