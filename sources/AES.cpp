#include "AES.hpp"
#include <iostream>

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

typename AES::byte*         AES::encrypt(byte *plaintext, byte *key, unsigned int len)
{
    check_length(len);

    byte            *ciphertext = new byte[len];
    byte            *round_keys = new byte[4 * NUM_COL * (num_rounds + 1)];

    key_expansion(key, round_keys);
    for (unsigned int i = 0; i < len; i += AES::BLOCK_SIZE)
    {
        encrypt_block(plaintext + i, ciphertext + i, round_keys);
    }

    delete[] round_keys;
    return ciphertext;
}


/* Private Util Functon Implementations */

void                        AES::sub_bytes(byte state[4][NUM_COL])
{
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < NUM_COL; j++)
        {
            byte temp = state[i][j];
            state[i][j] = SBOX[temp / 16][temp % 16];
        }
}

void                        AES::shift_row(byte state[4][NUM_COL], unsigned int rpos, unsigned int n)
{
    byte    temp[NUM_COL];

    for (unsigned int j = 0; j < NUM_COL; j++)
        temp[j] = state[rpos][(j + n) % NUM_COL];

    memcpy(state[rpos], temp, AES::BLOCK_SIZE / 4);
}

void                        AES::shift_rows(byte state[4][NUM_COL])
{
    shift_row(state, 1, 1);
    shift_row(state, 2, 2);
    shift_row(state, 3, 3);
}

void                        AES::mix_columns(byte state[4][NUM_COL])
{
    byte    temp_state[4][NUM_COL];

    for (size_t i = 0; i < 4; ++i)
        memset(temp_state[i], 0, 4);

    for (size_t i = 0; i < 4; ++i)
        for (size_t k = 0; k < 4; ++k)
            for (size_t j = 0; j < 4; ++j)
            {
                if (CMDS[i][k] == 1)
                    temp_state[i][j] ^= state[k][j];
                else
                    temp_state[i][j] ^= GF_MUL_TABLE[CMDS[i][k]][state[k][j]];
            }

    for (size_t i = 0; i < 4; ++i)
        memcpy(state[i], temp_state[i], 4);
}

void                        AES::sub_word(byte *word)
{
    for (int i = 0; i < 4; i++)
        word[i] = SBOX[word[i] / 16][word[i] % 16];
}

void                        AES::rot_word(byte *word)
{
    byte temp = word[0];

    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

void                        AES::xor_words(byte *a, byte *b, byte *c)
{
    for (int i = 0; i < 4; i++)
        c[i] = a[i] ^ b[i];
}

typename AES::byte          AES::x_mult(byte b)
{
    return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
}

void                        AES::round_const(byte *word, unsigned int n)
{
    unsigned char c = 1;

    for (unsigned int i = 0; i < n - 1; i++)
        c = x_mult(c);

    word[0] = c;
    word[1] = word[2] = word[3] = 0;
}

void            AES::add_round_key(byte state[4][NUM_COL], byte *key)
{
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < NUM_COL; j++)
            state[i][j] = state[i][j] ^ key[i + 4 * j];
}


void                        AES::key_expansion(const byte *key, byte *w)
{
    unsigned char word[4];    // 32-bit word
    unsigned char rcon[4];    // round constants
    unsigned int  i = 0;
  
  // copying the original key 
 
    while (i < num_words * 4)
    {
        w[i] = key[i];
        i++;
    }

  // key expansion loop

    i = 4 * num_words;
    while (i < 4 * NUM_COL * (num_rounds + 1))
    {
      // temporary word update

        word[0] = w[i - 4 + 0];
        word[1] = w[i - 4 + 1];
        word[2] = w[i - 4 + 2];
        word[3] = w[i - 4 + 3];

      // round constant update

        if (i / 4 % num_words == 0) 
        {
            rot_word(word);
            sub_word(word);
            round_const(rcon, i / (num_words * 4));
            xor_words(word, rcon, word);
        }
        else if (num_words > 6 && i / 4 % num_words == 4)
            sub_word(word);

      // expanded key update
      
        w[i + 0] = w[i + 0 - 4 * num_words] ^ word[0];
        w[i + 1] = w[i + 1 - 4 * num_words] ^ word[1];
        w[i + 2] = w[i + 2 - 4 * num_words] ^ word[2];
        w[i + 3] = w[i + 3 - 4 * num_words] ^ word[3];

        i += 4;
    }
}


void                        AES::encrypt_block(const byte *in, byte *out, byte *round_keys)
{
    byte            state[4][NUM_COL];

    // initialize the state

    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < NUM_COL; j++)
            state[i][j] = in[i + (4 * j)];

    add_round_key(state, round_keys);

    // encryption loop

    for (unsigned int round = 1; round <= num_rounds - 1; round++)
    {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, round_keys + round * 4 * NUM_COL);
    }
    
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, round_keys + num_rounds * 4 * NUM_COL);

    // copy the state in output
    
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < NUM_COL; j++)
            out[i + 4 * j] = state[i][j];

}

void                        AES::check_length(unsigned int len)
{
    if (len % AES::BLOCK_SIZE != 0)
        throw std::length_error("Plaintext must be devisible by " 
                +  std::to_string(AES::BLOCK_SIZE));
}
