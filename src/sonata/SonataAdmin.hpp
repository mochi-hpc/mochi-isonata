/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Admin.hpp>
#include <sonata/Admin.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class SonataAdmin : public AbstractAdminImpl {

  sonata::Admin admin;

public:

  template<typename ... Args>
  SonataAdmin(Args&&... args)
  : admin(std::forward<Args>(args)...) {}

  virtual ~SonataAdmin() {}

  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token) const override {
    admin.createDatabase(address, provider_id, name, type, config, token);
  }

  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const char *config, const std::string &token) const override {
    admin.createDatabase(address, provider_id, name, type, config, token);
  }

  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token) const override {
    admin.createDatabase(address, provider_id, name, type, config, token);
  }

  void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token) const override {
    admin.attachDatabase(address, provider_id, name, type, config, token);
  }

  void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token) const override {
    admin.attachDatabase(address, provider_id, name, type, config, token);
  }

  void detachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token) const override {
    admin.detachDatabase(address, provider_id, name, token);
  }

  void destroyDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token) const override {
    admin.destroyDatabase(address, provider_id, name);
  }

  std::vector<std::string> listDatabases(
        const std::string &address,
        uint16_t provider_id,
        const std::string &token) const override {
    return admin.listDatabases(address, provider_id, token);
  }

  void shutdownServer(const std::string &address) const override {
    admin.shutdownServer(address);
  }

  operator bool() const override {
    return admin;
  }
};

}
