/*
 * snode.c - a slim toolkit for network communication
 * Copyright (C) 2020, 2021 Volker Christian <me@vchrist.at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"      // IWYU pragma: keep
#include "core/SNodeC.h" // for SNodeC
#include "log/Logger.h"  // for Writer
#include "model/servers.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

int main(int argc, char* argv[]) {
    core::SNodeC::init(argc, argv);

#if (STREAM_TYPE == LEGACY)
    std::map<std::string, std::any> options = {{}};
#elif (STREAM_TYPE == TLS)
    std::map<std::string, std::any> options = {
        {"CertChain", SERVERCERTF}, {"CertChainKey", SERVERKEYF}, {"Password", KEYFPASS}, {"CaFile", CLIENTCAFILE}};

    std::map<std::string, std::any> sniCert = {
        {"CertChain", SNODECCERTF}, {"CertChainKey", SERVERKEYF}, {"Password", KEYFPASS}, {"CaFile", CLIENTCAFILE}};
#endif

    using SocketServer = apps::echo::model::STREAM::EchoSocketServer;
    SocketServer server = apps::echo::model::STREAM::getServer(options);

#if (STREAM_TYPE == TLS)
    server.addSniCert("snodec.home.vchrist.at", sniCert);
#endif

#if (NET_TYPE == IN) // in
#if (STREAM_TYPE == LEGACY)
    server.listen(8080, 5, [](const SocketServer::Socket& socket, int errnum) -> void {
#elif (STREAM_TYPE == TLS)
    server.listen(8088, 5, [](const SocketServer::Socket& socket, int errnum) -> void {
#endif
#elif (NET_TYPE == IN6) // in6
#if (STREAM_TYPE == LEGACY)
    server.listen(8080, 5, [](const SocketServer::Socket& socket, int errnum) -> void {
#elif (STREAM_TYPE == TLS)
    server.listen(8088, 5, [](const SocketServer::Socket& socket, int errnum) -> void {
#endif
#elif (NET_TYPE == L2) //
    // DIONE: 10:3D:1C:AC:BA:9C
    // TITAN: A4:B1:C1:2C:82:37

    // USB: 44:01:BB:A3:63:32

    // server.listen("A4:B1:C1:2C:82:37", 0x1023, 5, [](const SocketServer::Socket& socket, int errnum) -> void { // titan
    server.listen("10:3D:1C:AC:BA:9C", 0x1023, 5, [](const SocketServer::Socket& socket, int errnum) -> void { // titan
#elif (NET_TYPE == RF) // rf
    // server.listen("A4:B1:C1:2C:82:37", 1, 5, [](const SocketServer::Socket& socket, int errnum) -> void { // titan
    server.listen("10:3D:1C:AC:BA:9C", 1, 5, [](const SocketServer::Socket& socket, int errnum) -> void { // titan
#elif (NET_TYPE == UN) // un
    server.listen("/tmp/testme", 5, [](const SocketServer::Socket& socket, int errnum) -> void { // titan
#endif
        if (errnum != 0) {
            PLOG(FATAL) << "listen";
        } else {
            VLOG(0) << "snode.c listening on " << socket.getBindAddress().toString();
        }

#ifdef NET_TYPE
    });
#endif

    return core::SNodeC::start();
}
