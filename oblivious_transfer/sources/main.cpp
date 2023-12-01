#include <iostream>
#include "rsa.hpp"

int main()
{
    rsa rsa_alg(47, 53);

    string message = "Hello RSA!";
    std::cout << "Original Message: " << message << std::endl;

    // Encryption
    vector<size_t> ciphertext = rsa_alg.encrypt(message);

    std::cout << "Encrypted Message: ";
    for (size_t c : ciphertext)
         std::cout << std::to_string(c);
    std::cout << std::endl;
    

    // Decryption
    string decrypted_message = rsa_alg.decrypt(ciphertext);
    std::cout << "Decrypted Message: " << decrypted_message << std::endl;

    return 0;
}
