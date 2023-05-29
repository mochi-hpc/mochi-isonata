/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Admin.hpp>
#include <isonata/Exception.hpp>
#include <yokan/cxx/admin.hpp>
#include <yokan/cxx/client.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class YokanAdmin : public AbstractAdminImpl {

  tl::engine    m_engine;
  yokan::Admin  m_admin;
  yokan::Client m_client;

public:

  YokanAdmin(const tl::engine& engine)
  : m_engine{engine}
  , m_admin{engine.get_margo_instance()}
  , m_client{engine.get_margo_instance()} {}

  virtual ~YokanAdmin() = default;

  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      m_admin.openNamedDatabase(
        ep.get_addr(), provider_id, token.c_str(), name.c_str(),
        type.c_str(), config.c_str());
  }

  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const char *config, const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      m_admin.openNamedDatabase(
        ep.get_addr(), provider_id, token.c_str(), name.c_str(),
        type.c_str(), config);
  }

  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      m_admin.openNamedDatabase(
        ep.get_addr(), provider_id, token.c_str(), name.c_str(),
        type.c_str(), config.dump().c_str());
  }

  void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      m_admin.openNamedDatabase(
        ep.get_addr(), provider_id, token.c_str(), name.c_str(),
        type.c_str(), config.c_str());
  }

  void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      m_admin.openNamedDatabase(
        ep.get_addr(), provider_id, token.c_str(), name.c_str(),
        type.c_str(), config.dump().c_str());
  }

  void detachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      auto db = m_client.findDatabaseByName(ep.get_addr(), provider_id, name.c_str());
      // TODO get db_id from db
      //m_admin.closeDatabase(ep.get_addr(), provider_id, token.c_str(), db_id);
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void destroyDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      auto db = m_client.findDatabaseByName(ep.get_addr(), provider_id, name.c_str());
      // TODO get db_id from db
      //m_admin.destroyDatabase(ep.get_addr(), provider_id, token.c_str(), db_id);
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  std::vector<std::string> listDatabases(
        const std::string &address,
        uint16_t provider_id,
        const std::string &token) const override {
      auto ep = m_engine.lookup(address);
      auto db_list = m_admin.listDatabases(ep.get_addr(), provider_id, token.c_str());
      // TODO get names from db ids
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void shutdownServer(const std::string &address) const override {
      auto ep = m_engine.lookup(address);
      m_engine.shutdown_remote_engine(ep);
  }

  operator bool() const override {
      return true;
  }
};

}
