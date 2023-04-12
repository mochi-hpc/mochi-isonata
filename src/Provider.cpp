#include <isonata/Provider.hpp>
#include <isonata/Exception.hpp>
#include <Config.hpp>
#ifdef ENABLE_SONATA
#include "SonataProvider.hpp"
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
        throw Exception("ISonata was not built with Sonata support", impl);
#endif
    }
    return Provider{}; // TODO
}

}
