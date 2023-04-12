/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __ISONATA_CLIENT_HPP
#define __ISONATA_CLIENT_HPP

#include <memory>
#include <isonata/Database.hpp>
#include <isonata/ProviderHandle.hpp>
#include <thallium.hpp>

namespace isonata {

class AbstractClientImpl {

public:

  virtual ~AbstractClientImpl() = default;

  virtual const thallium::engine &engine() const = 0;

  virtual Database open(
        const std::string &address, uint16_t provider_id,
        const std::string &db_name, bool check = true) const = 0;

  virtual Database open(
        const ProviderHandle &ph, const std::string &db_name,
        bool check = true) const {
        return open(static_cast<std::string>(ph), ph.provider_id(),
                    db_name, check);
  }

  virtual ProviderHandle createProviderHandle(
        const std::string &address, uint16_t provider_id) const = 0;

  virtual ProviderHandle createProviderHandle(
        hg_addr_t address, uint16_t provider_id) const = 0;

  virtual operator bool() const = 0;
};

/**
 * @brief The Client object is the main object used to establish
 * a connection with a Sonata service.
 */
class Client : public AbstractClientImpl {

  std::shared_ptr<AbstractClientImpl> self;

public:

  /**
   * @brief Factory function to create a client from a given backend
   * implementation (e.g. "sonata").
   *
   * @param engine Engine.
   * @param impl Implementation name.
   *
   * @return Client.
   */
  static Client create(const tl::engine& engine, const std::string& impl);

  Client();
  Client(Client&&) = default;
  Client(const Client&) = default;
  Client& operator=(Client&&) = default;
  Client& operator=(const Client&) = default;
  ~Client() = default;

  /**
   * @brief Returns the thallium engine used by the client.
   */
  const thallium::engine &engine() const override {
      return self->engine();
  }

  /**
   * @brief Opens a remote database and returns a
   * Database instance to access it. You may set "check" to false
   * if you know for sure that the corresponding database exists.
   *
   * @param address Address of the provider holding the database.
   * @param provider_id Provider id.
   * @param db_name Database name.
   * @param check Checks if the Database exists by issuing an RPC.
   *
   * @return a Database instance.
   */
  Database open(
        const std::string &address, uint16_t provider_id,
        const std::string &db_name, bool check = true) const override {
    return self->open(address, provider_id, db_name, check);
  }

  /**
   * @brief Same as above but use a provider handle instead of
   * a strinf address and provider id.
   *
   * @param ph Provider handle.
   * @param db_name Database name.
   * @param check Checks if the Database exists by issuing an RPC.
   *
   * @return a Database instance.
   */
  Database open(
        const ProviderHandle &ph, const std::string &db_name,
        bool check = true) const override {
    return self->open(ph, db_name, check);
  }

  /**
   * @brief Create a provider handle.
   *
   * @param address Address of the provider.
   * @param provider_id Provider id.
   *
   * @return A provider handle.
   */
  ProviderHandle createProviderHandle(
        const std::string &address, uint16_t provider_id) const override {
    return self->createProviderHandle(address, provider_id);
  }

  ProviderHandle createProviderHandle(
        hg_addr_t address, uint16_t provider_id) const override {
    return self->createProviderHandle(address, provider_id);
  }

  /**
   * @brief Checks that the Client instance is valid.
   */
  operator bool() const override {
    return self && *self;
  }
};

} // namespace isonata

#endif
