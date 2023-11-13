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

typename AES::byte*         AES::encrypt(byte *plaintext, byte *key)
{
    unsigned int    len = check_length(plaintext);
    byte            *ciphertext = new byte[len];
    byte            *round_keys = new byte[4 * NUM_COL * (num_rounds + 1)];

    key_expansion(key, round_keys);
    for (unsigned int i = 0; i < len; i += AES::BLOCK_SIZE)
        encrypt_block(plaintext + i, ciphertext + i, round_keys);

    delete[] round_keys;
    return ciphertext;
}


/* Private Util Functon Implementations */

unsigned int                AES::check_length(byte *text)
{
    unsigned int len = 0;
    while (text[len] != '\0')
        len++;

    if (len % AES::BLOCK_SIZE != 0)
        throw std::length_error("Plaintext must be devisible by " 
                +  std::to_string(AES::BLOCK_SIZE));

    return (len);
}

void                        AES::key_expansion(const byte *key, byte *w)
{
   //TODO: to be implemented 
}









