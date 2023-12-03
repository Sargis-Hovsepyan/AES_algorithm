#include <iostream>
#include "Receiver.hpp"

void    print(vector<size_t> v)
{
    for (size_t c : v)
        std::cout << static_cast<char>(c);
    std::cout << std::endl;
}

int main()
{
    RSA         rsa(43, 47);

    string      message_0 = "First Message!";
    string      message_1 = "Second Message!";
    int         choice = 0;

    /* Presenting the messages and the choice for OT */

    std::cout << "The first message: " << message_0 << std::endl;
    std::cout << "The second message: " << message_1 << std::endl;
    std::cout << "The original choice: " << choice << std::endl;;

    Sender      sender(message_0, message_1, rsa);
    Receiver    receiver(choice, sender);

    /* Showing the values of x and v from OT */

    Sender::pair    x = sender.get_random_messages();
    vector<size_t>  v = receiver.blind_encrypt(x[0], x[1]);


    std::cout << "\n\n";
    std::cout << "The value sent by the sender x_0: ";
    print(x[0]);
    std::cout << "The value sent by the sender x_1: ";
    print(x[1]);
    std::cout << "The value sent by the receiver v: ";
    print(v);

    /* Showing messages sent and chosen from OT */

    Sender::pair    messages = sender.send(v);
    vector<size_t>  chosen = receiver.receive(messages[0], messages[1]);

    std::cout << "\n\n";
    std::cout << "The message sent by the sender m_0: ";
    print(messages[0]);
    std::cout << "The message sent by the sender m_1: ";
    print(messages[1]);
    std::cout << "The message chosen by the receiver: ";
    print(chosen);

    return 0;
}
