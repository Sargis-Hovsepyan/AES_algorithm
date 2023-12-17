#include "rsa.hpp"

/* Constructors and Destructor */

RSA::RSA()
{
    long long p =  rand() % 1000;
    while (!miller_rabin_prime(p)) 
        p++;

    long long q = p + 1;
    while (!miller_rabin_prime(q)) 
        q++;

    long long phi;
    
    this->n = p * q;
    phi = (p - 1) * (q - 1);

    long long tmp = 2;
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

typename RSA::vct       RSA::encrypt(const vct& message)
{
    vector<long long>    encrypted;

    for (long long c : message)
        encrypted.push_back(mod_pow(c, this->e, this->n));

    return encrypted;
}

typename RSA::vct       RSA::decrypt(const vct& cipher)
{
    vector<long long>  decrypted;

    for (long long c : cipher)
        decrypted.push_back(mod_pow(c, this->d, this->n));

    return decrypted;
}

typename RSA::vct       RSA::get_public_key()
{
    vector<long long>    key;

    key.push_back(e);
    key.push_back(n);

    return key;
}

/* Private Util Functions */

bool                    RSA::is_prime(long long n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(n); i += 2)
        if (n % i == 0) return false;

    return true;
}

bool                    RSA::miller_rabin_prime(long long n)
{
    if (n == 0) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
	

    long long d = n - 1;
    long long r = 0;
	while (d % 2 == 0)
		r++, d >>= 1;

    // Now take a random integer between [2, n-2] as a
    for (int loop = 1; loop <= 15; loop++)
    {
        long long a = 2 + rand() % (n - 3);
		long long x = mod_pow(a, d, n);
		
        if (x == 1 || x == (n - 1))
            continue; // check again using different a
		
        long long i;
		for (i = 1; i < r; i++)
        {
			x = (x * x) % n;
			if (x == (n - 1))break; // check again using different a
		}

		if(i == r)
            return false; 
	}

	return true;
}

long long               RSA::gcd(long long a, long long b)
{
    if (b == 0)
        return a;

    return gcd(b, mod(a, b));
}

long long               RSA::mod(long long a, long long b)
{
    long long res = a % b;

    return (res < 0) ? (res + b) : res;
}

long long               RSA::mod_inverse(long long a, long long m)
{
    a = mod(a, m);
    if (a <= 1)
        return a;
    return mod(((1 - mod_inverse(m%a, a) * m)) / a, m);
}


long long               RSA::mod_pow(long long base, long long exponent, long long modulus) 
{
    base = mod(base, modulus);
    long long result = 1;

    while (exponent > 0)
    {
        if (exponent & 1) 
            result = mod((result * base), modulus);

        base = mod((base * base), modulus);
        exponent >>= 1;
    }

    return result;
}
