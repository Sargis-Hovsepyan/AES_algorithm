#ifndef AES_H
#define AES_H

#include "sbox.hpp"
#include "gfmul.hpp"

#include <vector>
#include <cstring>
#include <stdexcept>


enum class AESKeyLen 
{ 
    AES_128, 
    AES_192, 
    AES_256 
};

class AES 
{
    public:
        typedef unsigned char           byte;

    private:
        static const unsigned int   NUM_COL = 4;
        static const unsigned int   BLOCK_SIZE = 4 * NUM_COL * sizeof(unsigned char);

        unsigned int    num_rounds;
        unsigned int    num_words; // In Key

    public:
        /* Constructors & Destructor */

        explicit AES(const AESKeyLen key_len = AESKeyLen::AES_256);

        AES& operator=(const AES& src);
        AES(const AES& src);

        ~AES();

        /* Public Interface Functions */

        byte*           encrypt(byte *plaintext, byte *key, unsigned int len);  // ECB Mode
        byte*           decrypt(byte *ciphertext, byte *key, unsigned int len); // ECB Mode

        void            print_hex(byte *a, unsigned int n);

    private:
        /* Private Util Functions */

        void            sub_bytes(byte state[4][NUM_COL]);
        void            inv_sub_bytes(byte state[4][NUM_COL]);

        void            shift_row(byte state[4][NUM_COL], unsigned int rpos, unsigned int n);
        void            shift_rows(byte state[4][NUM_COL]);
        void            inv_shift_rows(byte state[4][NUM_COL]);

        void            mix_columns(byte state[4][NUM_COL]);
        void            inv_mix_columns(byte state[4][NUM_COL]);

        void            sub_word(byte *word);
        void            rot_word(byte *word);
        void            xor_words(byte *a, byte *b, byte *c);

        byte            x_mult(byte b);
        void            round_const(byte *word, unsigned int n);

        void            add_round_key(byte state[4][NUM_COL], byte *key);
        void            key_expansion(const byte *key, byte *w);

        void            encrypt_block(const byte *in, byte *out, byte *round_keys);
        void            decrypt_block(const byte *in, byte *out, byte *round_keys);

        void            check_length(unsigned int len);
};

#endif
