#ifndef _RECEIVER_HPP
#define _RECEIVER_HPP

#include "Sender.hpp"

class Receiver
{
    private:
        bool            c;
        vector<size_t>  k;

        Sender          s;

    public:
        /* Constructor and Destructor */

        Receiver(bool choice, const Sender& sender);
        ~Receiver();

        /* Public Interface Functions */

        vector<size_t>   blind_encrypt(const vector<size_t>& x_0, const vector<size_t>& x_1);
        vector<size_t>   receive(const vector<size_t>& m_0, const vector<size_t>& m_1);
};

#endif
