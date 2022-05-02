#include <list>
#include <snode.c/core/SNodeC.h>
#include <snode.c/net/in/stream/legacy/SocketServer.h>
#include <snode.c/core/socket/SocketContextFactory.h>
#include <core/socket/SocketContext.h>

class ChatApp{
private:
    ChatApp() = default;
    ChatApp(const ChatApp&) = delete;           //no copy constractor possible because of singelton

    ChatApp& operator=(const ChatApp&) = delete;

public:
    static ChatApp& instance(){
        static ChatApp chat;

        return chat;
    }

    void addServerContext(core::socket::ServerContext* serverContext){
        serverContexts.push_back(serverContext);
    }
    void removeServerContext(core::socket::ServerContext* serverContext){
        serverContexts.remove(serverContext);
    }

    void echoToAll(const std::string& text){
        for(core::socket::ServerContext* serverContext : serverContexts){
            serverContext->sendToPeer(text);
        }
    }

private:
    std::list<core::socket::ServerContext*> serverContexts;

};



class ServerContex : public core::socket::SocketContext {
public:
    explicit ServerContex(core::socket:SocketConnection* socketConnection)
        : core::socket::SocketContext(socketConnection){
    }

private:
    void onConnected() override{
        std::cout << "Context connected to Peer" << std::endl;
        ChatApp::instance().addServerContext(this);
    }

    void onDisconnected() override{
        std::cout << "Context disonnected from Peer" << std::endl;
        ChatApp::instance().removeServerContext(this);
    }

    void onReceiveFromPeer() override{
        char buffer[1024];

        ssize_t numBytesRead = readFromPeer(buffer, 1023);
        buffer[numBytesRead] = 0;

        std::cout << "Buffer: " << buffer << std::endl;

        //sendToPeer(buffer, numBytesRead);
        ChatApp::instance().echoToAll(std::string(buffer, numBytesRead));
    }

};



class ServerContextFactory : public core::socket::SocketContextFactory{
    core::socket::SocketContext* create([[maybe_unused]] core::socket::SocketConnection *socketConnection){
        return ServerContext(socketConnection);
    }
};

int main(int argc, char* argv[]){
    core::SNodeC::init(argc, argv);

    // server needs 3 callbacks:   1. on connect,  2. onConnected,     3. onDisconnect
    //alle drei brauchen ein Socket

    using Server =  net::in::stream::legacy::SocketServer<ServerContextFactory>;
    using SocketConnection = net::in::stream::legacy::SocketServer<ServerContextFactory>::SocketConnection;

    Server server(
        []([[maybe_unused]]SocketConnection* socketConnection) -> void{
            std::cout <<"OnConnection from: " << socketConnection->getRemoteAdress().ToString() << std::endl;

        },
        []([[maybe_unused]]SocketConnection* socketConnection) -> void{
            std::cout <<"OnConnection from: " << socketConnection->getRemoteAdress().ToString() << std::endl;
        },
        []([[maybe_unused]]SocketConnection* socketConnection) -> void{
            std::cout <<"OnDisconnect from: " << socketConnection->getRemoteAdress().ToString() << std::endl;
        });

    server.list(8080, 5, [](const Server::SocketAdress& socketAdress, int errum) -> void {
        if (errnum == 0){
            std::cout <<"Server listening on " << socketAdress.toString() << std::endl;
        }
        else{
           std::cout << "Error: Server trying to listen on " <<socketAdress.toString() << " : errno = " << errnum;
        }
    });

    do{
        core::SNodeC::tick(1);
        std::out << "tick" << std::endl;
    }while(true)

    //return core::SNodeC::start(); //dafür nutzen wir jetzt do while
}
