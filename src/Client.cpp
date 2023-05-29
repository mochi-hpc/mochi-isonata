#include <isonata/Client.hpp>
#include <Config.hpp>
#ifdef ENABLE_SONATA
#include "sonata/SonataClient.hpp"
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
    throw Exception("Unknown implementation backend \"" + impl + "\"");
}

}
