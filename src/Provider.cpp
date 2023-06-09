#include <isonata/Provider.hpp>
#include <isonata/Exception.hpp>
#include <Config.hpp>
#ifdef ENABLE_SONATA
#include "sonata/SonataProvider.hpp"
#endif
#ifdef ENABLE_YOKAN
#include "yokan/YokanProvider.hpp"
#endif

namespace isonata {

Provider Provider::create(thallium::engine& engine, const std::string& impl,
                          uint16_t provider_id, const std::string &config, const tl::pool &pool) {
    if(impl == "sonata") {
#ifdef ENABLE_SONATA
        auto provider = Provider{};
        provider.self = std::make_shared<SonataProvider>(engine, provider_id, config, pool);
        return provider;
#else
        throw Exception("ISonata was not built with Sonata support");
#endif
    }
    if(impl == "yokan") {
#ifdef ENABLE_YOKAN
        auto provider = Provider{};
        std::string cfg = config.empty() ? "{}" : config;
        provider.self = std::make_shared<YokanProvider>(
            engine.get_margo_instance(), provider_id, "",
            cfg.c_str(), pool.native_handle());
        return provider;
#else
        throw Exception("ISonata was not built with Yokan support");
#endif
    }
    throw Exception("Unknown implementation backend \"" + impl + "\"");
}

}
