#ifndef AES_H
#define AES_H

#include "sbox.hpp"
#include "gfmul.hpp"

#include <vector>

enum class AESKeyLen 
{ 
    AES_128, 
    AES_192, 
    AES_256 
};

class AES 
{
    typedef std::vector<unsigned char>  _vct;


    private:
        static const unsigned int   NUM_COL = 4;
        static const unsigned int   BLOCK_SIZE = 4 * NUM_COL * sizeof(unsigned char);

        unsigned int    num_rounds;
        unsigned int    num_words; // In Key

    public:
        /* Constructors & Destructor */

        explicit AES(const AESKeyLen key_len = AESKeyLen::AES_256);

        AES(const AES& src);
        AES& operator=(const AES& src);

        ~AES();

        /* Public Interface Functions */

        _vct            encrypt(_vct in, _vct key); // ECB Mode
        _vct            decrypt(_vct in, _vct key); // ECB Mode

        void            print_hex(_vct a);

    private:
        /* Private Util Functions */

        void            sub_bytes(unsigned char state[4][NUM_COL]);
        void            inv_sub_bytes(unsigned char state[4][NUM_COL]);

        void            shift_row(unsigned char state[4][NUM_COL], unsigned int rpos, unsigned int n);
        void            shift_rows(unsigned char state[4][NUM_COL]);
        void            inv_shift_rows(unsigned char state[4][NUM_COL]);

        void            mix_columns(unsigned char state[4][NUM_COL]);
        void            inv_mix_columns(unsigned char state[4][NUM_COL]);

        void            sub_word(unsigned char *a);
        void            rot_word(unsigned char *a);
        void            xor_words(unsigned char *a, unsigned char *b, unsigned char *c);

        void            add_round_key(unsigned char state[4][NUM_COL], unsigned char *key);
        void            key_expansion(const unsigned char *key, unsigned char *w);

        void            encrypt_block(const unsigned char *in, unsigned char *out, unsigned char *key);
        void            decrypt_block(const unsigned char *in, unsigned char *out, unsigned char *key);

        void            check_length(unsigned int len);
        unsigned char   mult(unsigned char b);
};

#endif
