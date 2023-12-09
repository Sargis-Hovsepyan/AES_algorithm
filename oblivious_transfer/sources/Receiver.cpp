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

vector<long long>   Receiver::blind_encrypt(const vector<long long>& x_0, const vector<long long>& x_1)
{
    vector<long long>  key = s.get_public_key();
    vector<long long>  x = (this->c) ? x_1 : x_0;
    vector<long long>  v;

    for (int i = 0; i < 16; ++i)
        this->k.push_back((rand() % 512) % key[1]);
    
    vector<long long> k_enc = s.encrypt(k);
    for (size_t i = 0; i < k.size(); ++i)
        v.push_back((x[i] + k_enc[i]) % key[1]);

    return v;
}

vector<long long>   Receiver::receive(const vector<long long>& m_0, const vector<long long>& m_1)
{
    vector<long long>  m = (this->c) ? m_1 : m_0;
    vector<long long>  choice;

    for (size_t i = 0; i < m.size(); ++i)
        choice.push_back(m[i] - k[i]);

    return choice;
}
