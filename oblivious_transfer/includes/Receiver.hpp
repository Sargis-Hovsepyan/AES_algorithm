#ifndef _RECEIVER_HPP
#define _RECEIVER_HPP

#include "Sender.hpp"

class Receiver
{
    private:
        bool                c;
        vector<long long>   k;

        Sender              s;

    public:
        /* Constructor and Destructor */

        Receiver(bool choice, const Sender& sender);
        ~Receiver();

        /* Public Interface Functions */

        vector<long long>   blind_encrypt(const vector<long long>& x_0, const vector<long long>& x_1);
        vector<long long>   receive(const vector<long long>& m_0, const vector<long long>& m_1);
};

#endif
