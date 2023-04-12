/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __ISONATA_ADMIN_HPP
#define __ISONATA_ADMIN_HPP

#include <isonata/Exception.hpp>
#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <thallium.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class AbstractAdminImpl {

public:

  virtual ~AbstractAdminImpl() = default;

  virtual void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token) const = 0;

  virtual void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const char *config, const std::string &token) const {
            createDatabase(
                address, provider_id, name, type,
                config ? std::string(config) : "{}",
                token);
  }

  virtual void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token) const {
            createDatabase(
                address, provider_id, name, type,
                config.dump(), token);
  }

  virtual void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token) const = 0;

  virtual void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token) const {
            attachDatabase(
                address, provider_id, name, type, config.dump(), token);
  }

  virtual void detachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token) const = 0;

  virtual void destroyDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token) const = 0;

  virtual std::vector<std::string> listDatabases(
        const std::string &address,
        uint16_t provider_id,
        const std::string &token) const = 0;

  virtual void shutdownServer(const std::string &address) const = 0;

  virtual operator bool() const = 0;
};

/**
 * @brief Admin interface to a Sonata service. Enables creating
 * and destroying databases, and attaching and detaching them
 * from a provider. If Sonata providers have set up a security
 * token, operations from the Admin interface will need this
 * security token.
 */
class Admin : public AbstractAdminImpl {

  std::shared_ptr<AbstractAdminImpl> self;

  Admin() = default;

public:

  Admin(Admin&&) = default;
  Admin(const Admin&) = default;
  Admin& operator=(const Admin&) = default;
  Admin& operator=(Admin&&) = default;

  /**
   * @brief Factory function to create an admin from a given backend
   * implementation (e.g. "sonata").
   *
   * @param engine Engine.
   * @param impl Implementation name.
   *
   * @return Admin.
   */
  static Admin create(const tl::engine& engine, const std::string& impl);

  /**
   * @brief Creates a database on the target provider.
   * The config string must be a JSON object acceptable
   * by the desired backend's creation function.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to create.
   * @param type Type of the database to create.
   * @param config JSON configuration for the database.
   * @param token Security token.
   */
  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token = "") const override {
    try {
      self->createDatabase(address, provider_id, name, type, config, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Creates a database on the target provider.
   * The config string must be a JSON object acceptable
   * by the desired backend's creation function.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to create.
   * @param type Type of the database to create.
   * @param config JSON configuration for the database.
   * @param token Security token.
   */
  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const char *config, const std::string &token = "") const override {
    try {
      self->createDatabase(address, provider_id, name, type, config, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Creates a database on the target provider.
   * The config object must be a JSON object acceptable
   * by the desired backend's creation function.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to create.
   * @param type Type of the database to create.
   * @param config JSON configuration for the database.
   * @param token Security token.
   */
  void createDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token = "") const override {
    try {
      self->createDatabase(address, provider_id, name, type, config, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Attaches an existing database to the target provider.
   * The config string must be a JSON object acceptable
   * by the desired backend's attach function.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to create.
   * @param type Type of the database to create.
   * @param config JSON configuration for the database.
   * @param token Security token.
   */
  void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const std::string &config,
        const std::string &token = "") const override {
    try {
      self->attachDatabase(address, provider_id, name, type, config, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Attaches an existing database to the target provider.
   * The config object must be a JSON object acceptable
   * by the desired backend's attach function.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to create.
   * @param type Type of the database to create.
   * @param config JSON configuration for the database.
   * @param token Security token.
   */
  void attachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name, const std::string &type,
        const json &config,
        const std::string &token = "") const override {
    try {
      self->attachDatabase(address, provider_id, name, type, config, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Detach an attached database from the target provider.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to detach.
   * @param token Security token.
   */
  void detachDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token = "") const override {
    try {
      self->detachDatabase(address, provider_id, name, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Destroys an attached database from the target provider.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param name Name of the database to destroy.
   * @param token Security token.
   */
  void destroyDatabase(
        const std::string &address, uint16_t provider_id,
        const std::string &name,
        const std::string &token = "") const override {
    try {
      self->destroyDatabase(address, provider_id, name, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Returns the list of database names managed by the target provider.
   *
   * @param address Address of the target provider.
   * @param provider_id Provider id.
   * @param token Security token.
   */
  std::vector<std::string> listDatabases(
        const std::string &address,
        uint16_t provider_id,
        const std::string &token = "") const override {
    try {
      return self->listDatabases(address, provider_id, token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Shuts down the target server. The Thallium engine
   * used by the server must have remote shutdown enabled.
   *
   * @param address Address of the server to shut down.
   */
  void shutdownServer(const std::string &address) const override {
    try {
      return self->shutdownServer(address);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Checks if the object is valid.
   */
  operator bool() const override {
    try {
      return self && *self;
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }
};

} // namespace isonata

#endif
