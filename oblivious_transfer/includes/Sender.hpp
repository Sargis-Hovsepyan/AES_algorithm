#ifndef _SENDER_HPP_
#define _SENDER_HPP_

#include "rsa.hpp"
#include <openssl/sha.h>

class Sender
{
    typedef vector<vector<size_t>>  pair;

    private:
        vector<size_t>  message_0, x_0;
        vector<size_t>  message_1, x_1;
        RSA             rsa;
    
    public:
        /* Constructor and Destructor */

        Sender(const string& msg_0, const string& msg_1, RSA& sender_rsa);
        ~Sender();

        /* Public Interface Functions */

        vector<size_t>      get_public_key();
        vector<size_t>      encrypt(const vector<size_t>& data);

        pair                get_random_messages();
        pair                send(const vector<size_t>& v);

        pair                blind_decrypt(const vector<size_t>& v);
};

#endif
