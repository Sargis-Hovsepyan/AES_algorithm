#include "AES.hpp"

/* Constructors & Destructor Implementations */

AES::AES(const AESKeyLen key_len)
{
    switch(key_len)
    {
        case AESKeyLen::AES_128:
            this->num_words = 4;
            this->num_rounds = 10;
            break;
        case AESKeyLen::AES_192:
            this->num_words = 6;
            this->num_rounds = 12;
            break;
        case AESKeyLen::AES_256:
            this->num_words = 8;
            this->num_rounds = 14;
            break;
    }
}

AES&    AES::operator=(const AES& src)
{
    this->num_words = src.num_words;
    this->num_rounds = src.num_rounds;

    return (*this);
}

AES::AES(const AES& src) { *this = src; }

AES::~AES() { }


/* Public Interface Function Implementations */

