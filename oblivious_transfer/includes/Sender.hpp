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

        Sender(vector<size_t>& msg_0, vector<size_t>& msg_1, RSA& sender_rsa);
        ~Sender();

        /* Public Interface Functions */

        vector<size_t>      send_public_key();
        pair                send_random_messages();

        pair                send_choices(vector<size_t>& v);
};

#endif
