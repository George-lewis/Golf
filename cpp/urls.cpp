//////////////////////////////////////////////////////////////
// Just some C++ that makes use of networking system calls. //
//////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

#include <netdb.h>
#include <netinet/in.h> 
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef std::vector<std::string> IPS;

struct URL {
    std::string protocol, _hostname, domain;
    auto construct() const {
        return protocol + "://" + _hostname + '.' + domain;
    }
    auto hostname() const {
        return _hostname + '.' + domain;
    }
    int port() const {
        return getservbyname(protocol.c_str(), NULL)->s_port;
    }
    IPS ips() const {
        IPS ips;
        struct addrinfo *result;
        int res = getaddrinfo(hostname().c_str(), NULL, NULL, &result);
        if (res != 0) {
            std::cout << gai_strerror(res) << '\n';
            freeaddrinfo(result);
            return ips;
        }
        for (; result != NULL; result = result->ai_next) {
            ips.emplace_back( inet_ntoa( reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr ) );
        }
        freeaddrinfo(result);
        return ips;
    }
};

typedef std::vector<URL> URLS;

std::ostream& operator<<(std::ostream& os, const URL& url) {
    os << url.construct();
    return os;
}

std::ostream& operator<<(std::ostream& os, const URLS& urls) {
    for (URLS::size_type i = 0; i < urls.size(); i++) {
        os << urls[i];
        if ( i != urls.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const IPS& ips) {
    for (IPS::size_type i = 0; i < ips.size(); i++) {
        os << ips[i];
        if ( i != ips.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

int main() {

    URL google = { "https", "google", "ca" }, me = { "https", "georgelewis", "ca" }, yt = { "https", "youtube", "com" };

    URLS urls{google, me, yt};

    for (const auto& u : urls) {
        std::cout << u.construct() << " - " << u.ips() << '\n';
    }

}
