/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "YokanDatabase.hpp"
#include <isonata/Client.hpp>
#include <isonata/Exception.hpp>
#include <yokan/cxx/client.hpp>

namespace isonata {

class YokanClient : public AbstractClientImpl {

  tl::engine    m_engine;
  yokan::Client m_client;

public:

  YokanClient(const tl::engine& engine)
  : m_engine(engine)
  , m_client(engine.get_margo_instance()) {}

  ~YokanClient() {}

  const thallium::engine &engine() const override {
      return m_engine;
  }

  Database open(
        const std::string &address, uint16_t provider_id,
        const std::string &db_name, bool check) const override {
      (void)check;
      auto ep = m_engine.lookup(address);
      auto db = m_client.findDatabaseByName(ep.get_addr(), provider_id, db_name.c_str());
      return Database{std::make_shared<YokanDatabase>(m_engine, db)};
  }

  Database open(
        const ProviderHandle &ph, const std::string &db_name,
        bool check) const override {
      auto db = m_client.findDatabaseByName(ph.get_addr(), ph.provider_id(), db_name.c_str());
      return Database{std::make_shared<YokanDatabase>(m_engine, db)};
  }

  ProviderHandle createProviderHandle(
        const std::string &address, uint16_t provider_id) const override {
      auto ep = m_engine.lookup(address);
      return ProviderHandle{ep, provider_id};
  }

  ProviderHandle createProviderHandle(
        hg_addr_t address, uint16_t provider_id) const override {
      auto ep = tl::endpoint(m_engine, address, false);
      return ProviderHandle{ep, provider_id};
  }

  operator bool() const override {
      return true;
  }
};

} // namespace isonata
