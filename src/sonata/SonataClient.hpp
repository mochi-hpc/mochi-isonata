/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "SonataDatabase.hpp"
#include <isonata/Client.hpp>
#include <sonata/Client.hpp>

namespace isonata {

class SonataClient : public AbstractClientImpl {

  sonata::Client client;

public:

  template<typename ... Args>
  SonataClient(Args&&... args)
  : client(std::forward<Args>(args)...) {}

  ~SonataClient() {}

  const thallium::engine &engine() const override {
    return client.engine();
  }

  Database open(
        const std::string &address, uint16_t provider_id,
        const std::string &db_name, bool check) const {
    return Database{std::make_shared<SonataDatabase>(client.open(address, provider_id, db_name, check))};
  }

  Database open(
        const ProviderHandle &ph, const std::string &db_name,
        bool check) const override {
    return Database{
        std::make_shared<SonataDatabase>(client.open(ph, db_name, check))};
  }

  ProviderHandle createProviderHandle(
        const std::string &address, uint16_t provider_id) const override {
    return client.createProviderHandle(address, provider_id);
  }

  ProviderHandle createProviderHandle(
        hg_addr_t address, uint16_t provider_id) const override {
    return client.createProviderHandle(address, provider_id);
  }

  operator bool() const override {
    return client;
  }
};

} // namespace isonata
