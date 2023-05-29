#include <isonata/Admin.hpp>
#include <Config.hpp>
#ifdef ENABLE_SONATA
#include "sonata/SonataAdmin.hpp"
#endif
#ifdef ENABLE_YOKAN
#include "yokan/YokanAdmin.hpp"
#endif

namespace isonata {

Admin Admin::create(const thallium::engine& engine, const std::string& impl) {

    if(impl == "sonata") {
#ifdef ENABLE_SONATA
        auto admin = Admin{};
        admin.self = std::make_shared<SonataAdmin>(engine);
        return admin;
#else
        throw Exception("ISonata was not built with Sonata support");
#endif
    }
    if(impl == "yokan") {
#ifdef ENABLE_YOKAN
        auto admin = Admin{};
        admin.self = std::make_shared<YokanAdmin>(engine);
        return admin;
#else
        throw Exception("ISonata was not built with Yokan support");
#endif
    }
    throw Exception("Unknown implementation backend \"" + impl + "\"");
}

}
