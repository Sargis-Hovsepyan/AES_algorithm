#include "Sender.hpp"

/* Constructor and Destructor */

Sender::Sender(const string& msg_0, const string& msg_1, RSA& sender_rsa)
    : rsa(sender_rsa)
{
    for (char c : msg_0)
        this->message_0.push_back(static_cast<size_t>(c));

    for (char c : msg_1)
        this->message_1.push_back(static_cast<size_t>(c));
}

Sender::~Sender() 
{

}


/* Public Interface Functions */

vector<size_t>              Sender::get_public_key()
{
    return this->rsa.get_public_key();
}

vector<size_t>              Sender::encrypt(const vector<size_t>& data)
{
    return rsa.encrypt(data);
}

typename Sender::pair       Sender::get_random_messages()
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

typename Sender::pair       Sender::send(const vector<size_t>& v)
{
    pair            choices(2);
    pair            k;

    k = blind_decrypt(v);
    for (size_t i = 0; i < k[0].size(); i++)
    {
        choices[0].push_back(message_0[i] + k[0][i]);
        choices[1].push_back(message_1[i] + k[1][i]);
    }

    return choices;
}

typename Sender::pair       Sender::blind_decrypt(const vector<size_t>& v)
{
    pair            k(2);

    for (size_t i = 0; i < v.size(); i++)
    {
        k[0].push_back(v[i] - x_0[i]);
        k[1].push_back(v[i] - x_1[i]);
    }

    k[0] = rsa.decrypt(k[0]);
    k[1] = rsa.decrypt(k[1]);

    return k;
}
