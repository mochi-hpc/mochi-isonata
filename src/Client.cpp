#include <isonata/Client.hpp>
#include <Config.hpp>
#ifdef ENABLE_SONATA
#include "sonata/SonataClient.hpp"
#endif
#ifdef ENABLE_YOKAN
#include "yokan/YokanClient.hpp"
#endif

namespace isonata {

Client Client::create(const thallium::engine& engine, const std::string& impl) {

    if(impl == "sonata") {
#ifdef ENABLE_SONATA
        auto admin = Client{};
        admin.self = std::make_shared<SonataClient>(engine);
        return admin;
#else
        throw Exception("ISonata was not built with Sonata support");
#endif
    }
    if(impl == "yokan") {
#ifdef ENABLE_YOKAN
        auto admin = Client{};
        admin.self = std::make_shared<YokanClient>(engine);
        return admin;
#else
        throw Exception("ISonata was not built with Yokan support");
#endif
    }
    throw Exception("Unknown implementation backend \"" + impl + "\"");
}

}
