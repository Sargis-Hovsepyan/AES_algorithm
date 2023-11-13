#ifndef AES_H
#define AES_H

#include "sbox.hpp"
#include "gfmul.hpp"

enum class AESKeyLen 
{ 
    AES_128, 
    AES_192, 
    AES_256 
};

class AES 
{
    private:
        static const unsigned int   NUM_COL = 4;
        static const unsigned int   BLOCK_SIZE = 4 * NUM_COL * sizeof(unsigned char);

        unsigned int    num_rounds;
        unsigned int    num_words; // In Key

    public:
        explicit AES(const AESKeyLen key_len = AESKeyLen::AES_256);

        // TODO: complete the encrypt/decrypt function declarations
};

#endif
