#include "ClientContext.h"

#include <snode.c/core/SNodeC.h>
#include <net/in/stream/legacy/SocketClient.h>
#include <string>


int main([[maby_unused]] int arg, [[maby_unused]] char * argv[]){

    using Client = net::in::stream::legacy::SocketClient<ClientContextFactory>;
    using SocketConnection = Client::SocketConnection;

    core::SNodeC::init(argc, argv);

    Client client(
                []([[maybe_unused]]SocketConnection* socketConnection) -> void{
                    std::cout <<"OnConnection from: " << socketConnection->getRemoteAdress().ToString() << std::endl;

                },
                []([[maybe_unused]]SocketConnection* socketConnection) -> void{
                    std::cout <<"OnConnection from: " << socketConnection->getRemoteAdress().ToString() << std::endl;
                },
                []([[maybe_unused]]SocketConnection* socketConnection) -> void{
                    std::cout <<"OnDisconnect from: " << socketConnection->getRemoteAdress().ToString() << std::endl;
                });

    client.connect("localhost", 8080, [](const Client::SocketAdress& socketAdress, int errum) -> void {
        if (errnum == 0){
            std::cout <<"Client connected to " << socketAdress.toString() << std::endl;
        }
        else{
           std::cout << "Error: Client trying to listen on " <<socketAdress.toString() << " : errno = " << errnum;
        }
    });

    return core::SnodeC::start();
}
