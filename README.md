# AUA CS 215 Project... AES Algorithm Implementation

This project aims to provide a comprehensive and efficient implementation of the 
Advanced Encryption Standard (AES) algorithm in C++. AES is a widely used symmetric 
encryption algorithm that ensures secure communication and data protection. 

This implementation covers both encryption and decryption processes, allowing users 
to integrate AES encryption into their C++ applications.


## Usage

**This class is very simple to use:**
```c++
...
unsigned char plain[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff }; //plaintext example
unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }; //key example
unsigned int size = 16 * sizeof(unsigned char);  //bytes in plaintext

AES aes(AESKeyLen::AES_128);  ////128 - key length, can be 128, 192 or 256
c = aes.encrypt(plain, key, size);
//now variable c contains size bytes - ciphertext
...
```
Only the ECB mode is supported.


## Padding

This library does not provide any padding because padding is not part of AES standard. Plaintext and ciphertext length in bytes must be divisible by 16. If length doesn't satisfy this condition exception will be thrown

## Links

* [Wiki](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
* [NIST](https://www.nist.gov/publications/advanced-encryption-standard-aes)

## Development

For getting the code in local do 
`git clone https://github.com/Sargis-Hovsepyan/AES_algorithm.git`

The library of AES is in the folder of includes under `includes/AES.hpp` and the 
implementation is in sources folder under `sources/AES.cpp`. The main file runst some 
simple tests that can be found in `includes/aes_tests.hpp`
