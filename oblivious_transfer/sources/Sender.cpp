#include "Sender.hpp"

/* Constructor and Destructor */

Sender::Sender(vector<size_t>& msg_0, vector<size_t>& msg_1, RSA& sender_rsa)
    : rsa(sender_rsa)
{
    this->message_0 = msg_0;
    this->message_1 = msg_1;
}

Sender::~Sender() 
{

}


/* Public Interface Functions */

vector<size_t>              Sender::send_public_key()
{
    return this->rsa.get_public_key();
}

typename Sender::pair       Sender::send_random_messages()
{
    vector<vector<size_t>>  messages(2);

    for (int i = 0; i < 16; ++i)
    {
        x_0.push_back(rand() % 512);
        x_1.push_back(rand() % 512);
    }

    messages.push_back(x_0);
    messages.push_back(x_1);

    return messages;
}

typename Sender::pair       Sender::send_choices(vector<size_t>& v)
{
    vector<size_t>  k_0(v.size()), m_0(v.size());
    vector<size_t>  k_1(v.size()), m_1(v.size());
    pair            choices;

    for (size_t i = 0; i < v.size(); i++)
    {
        k_0.push_back(v[i] - x_0[i]);
        k_1.push_back(v[i] - x_1[i]);
    }

    k_0 = rsa.decrypt(k_0);
    k_1 = rsa.decrypt(k_1);

    for (size_t i = 0; i < k_0.size(); i++)
    {
        m_0.push_back(message_0[i] + k_0[i]);
        m_1.push_back(message_1[i] + k_1[i]);
    }

    choices.push_back(m_0);
    choices.push_back(m_1);

    return choices;
}
