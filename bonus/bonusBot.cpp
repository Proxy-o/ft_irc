#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <server IP> <server port> <server password>" << std::endl;
        return 1;
    }

    std::string SERVER_IP = std::string(argv[1]);
    int SERVER_PORT = std::atoi(argv[2]);
    std::string password = std::string(argv[3]);

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP.c_str(), &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr *)(&serverAddr), sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error connecting to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    std::string passCommand = "PASS " + password + "\n NICK bot\n USER bonusBot 0 * :bonusBot\n";
    send(clientSocket, passCommand.c_str(), passCommand.size(), 0);
    char buffer[4096];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0)
        {
            std::cerr << "Connection closed by the server." << std::endl;
            break;
        }
        std::string message(buffer);
        std::string sender = message.substr(1, message.find("!") - 1);
        message = message.substr(message.find("PRIVMSG bot :") + 13);
        std::string replay = "";
        {
        if (message == "hello\r\n")
        {
            replay = "hi how can i help you?\r\n";
        }
        else if (message == "how are you?\r\n")
        {
            replay = "i'm fine thanks\r\n";
        }
        else if (message == "what is your name?\r\n")
        {
            replay = "my name is bonusBot\r\n";
        }
        else if (message == "how old are you\r\n")
        {
            replay = "i'm older than zaki\r\n";
        }
        else if (message.find("give me") != std::string::npos)
        {
            replay = "no i can't give you sorry\r\n";
        }
        else if (message.find("what is") != std::string::npos)
        {
            replay = "ask google\r\n";
        }
        else if (message.find("did you") != std::string::npos)
        {
            replay = "no sry i did'not\r\n";
        }
        else if (message.find("write me") != std::string::npos)
        {
            replay = "these is a short story : once upon a time there was a bot called bonusBot he was very smart and he was created by taitans\r\n";
        }
        else if (message.find("cv") != std::string::npos)
        {
            replay = "cv hmdoullah o nta?\r\n";
        }
         else if (message.find("moumkin") != std::string::npos)
        {
            replay = "la mn9drch sorry?\r\n";
        }
         else if (message.find("wach") != std::string::npos)
        {
            replay = "oui possible\r\n";
        }
         else if (message.find("ila") != std::string::npos)
        {
            replay = "can you talk english\r\n";
        }
         else if (message.find("ach") != std::string::npos)
        {
            replay = "hhh \r\n";
        }
        else if (message.find("ping") != std::string::npos)
        {
            replay = "pong \r\n";
        }
        else if (message.find("pong") != std::string::npos)
        {
            replay = "ping \r\n";
        }
        else if (message.find("bye") != std::string::npos)
        {
            replay = "bye bye \r\n";
        }
        else if (message.find("good") != std::string::npos)
        {
            replay = "good luck \r\n";
        }
        else if (message.find("bad") != std::string::npos)
        {
            replay = "sorry \r\n";
        }
        else if (message.find("ok") != std::string::npos)
        {
            replay = "ok \r\n";
        }
        else if (message.find("no") != std::string::npos)
        {
            replay = "yes \r\n";
        }
        else if (message.find("yes") != std::string::npos)
        {
            replay = "no \r\n";
        }
        else if (message.find("help") != std::string::npos)
        {
            replay = "i can't help you sorry \r\n";
        }
        else if (message.find("what") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("who") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("where") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("when") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("why") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("how") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("do") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else if (message.find("can") != std::string::npos)
        {
            replay = "i don't know \r\n";
        }
        else
        {
            replay = "I'm sorry for any confusion, but as a text-based AI developed by OpenAI, I don't have the capability to understand your request. Please try rephrasing your request or asking a different question.\r\n";
        }
        }
        if (replay != "" && sender != "bot")
        {
            replay = "PRIVMSG " + sender + " :" + replay;
            send(clientSocket, replay.c_str(), replay.size(), 0);
            replay = "";
        }
    }
    close(clientSocket);

    return 0;
}
