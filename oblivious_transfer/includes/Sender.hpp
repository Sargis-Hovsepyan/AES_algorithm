#ifndef _SENDER_HPP_
#define _SENDER_HPP_

#include "rsa.hpp"
#include <openssl/sha.h>

class Sender
{
    public:
        typedef vector<vector<long long>>  pair;

    private:
        vector<long long>  message_0, x_0;
        vector<long long>  message_1, x_1;
        RSA             rsa;
    
    public:
        /* Constructor and Destructor */

        Sender(const string& msg_0, const string& msg_1, RSA& sender_rsa);
        ~Sender();

        /* Public Interface Functions */

        vector<long long>   get_public_key();
        vector<long long>   encrypt(const vector<long long>& data);

        pair                get_random_messages();
        pair                send(const vector<long long>& v);

        pair                blind_decrypt(const vector<long long>& v);
};

#endif
