#include "AES.hpp"
#include <iostream>

const unsigned int BLOCK_LENGTH = 16 * sizeof(unsigned char);

int main()
{
    AES aes(AESKeyLen::AES_128);

    AES::byte   plain[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    AES::byte   key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    
    AES::byte   *cipher = aes.encrypt(plain, key, BLOCK_LENGTH);
    AES::byte   *decrypted = aes.decrypt(cipher, key, BLOCK_LENGTH);

    std::cout << "plaintex HEX: "; 
    aes.print_hex(plain, BLOCK_LENGTH);
    
    std::cout << "ciphertext HEX: ";
    aes.print_hex(cipher, BLOCK_LENGTH);
    
    std::cout << "decrypted HEX: ";
    aes.print_hex(decrypted, BLOCK_LENGTH);

    return 0;
}
