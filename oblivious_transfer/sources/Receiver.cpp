#include "Receiver.hpp"

/* Constructor and Destructor */

Receiver::Receiver(bool choice, const Sender& sender) 
    : s(sender)
{
    this->c = choice;
}

Receiver::~Receiver() 
{

}


/* Public Interface Functions */

vector<size_t>      Receiver::blind_encrypt(const vector<size_t>& x_0, const vector<size_t>& x_1)
{
    vector<size_t>  key = s.get_public_key();
    vector<size_t>  x = (this->c) ? x_1 : x_0;
    vector<size_t>  v(x_0.size());

    for (int i = 0; i < 16; ++i)
        this->k.push_back(rand() % 512);

    vector<size_t>  k_encrypted = this->s.encrypt(k);

    for (size_t i = 0; i < v.size(); ++i)
        v.push_back((x[i] + k_encrypted[i]) % key[1]);

    return v;
}

vector<size_t>      Receiver::receive(const vector<size_t>& m_0, const vector<size_t>& m_1)
{
    vector<size_t>  m = (this->c) ? m_1 : m_0;
    vector<size_t>  choice(m.size());

    for (size_t i = 0; i < m.size(); ++i)
        choice.push_back(m[i] - k[i]);

    return choice;
}
