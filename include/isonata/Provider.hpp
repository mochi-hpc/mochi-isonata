/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __ISONATA_PROVIDER_HPP
#define __ISONATA_PROVIDER_HPP

#include <memory>
#include <string>
#include <thallium.hpp>
#include <isonata/Exception.hpp>

namespace isonata {

namespace tl = thallium;

class AbstractProviderImpl {

public:

  virtual ~AbstractProviderImpl() = default;

  virtual std::string getConfig() const = 0;

  virtual void setSecurityToken(const std::string &token) = 0;

  virtual operator bool() const = 0;
};

/**
 * @brief A Provider is an object that can receive RPCs
 * and dispatch them to specific databases.
 */
class Provider : public AbstractProviderImpl {

  std::shared_ptr<AbstractProviderImpl> self;

public:

  Provider() = default;
  Provider(Provider&&) = default;
  Provider(const Provider&) = default;
  Provider& operator=(const Provider&) = default;
  Provider& operator=(Provider&&) = default;

  /**
   * @brief Factory function to create a provider from a given backend
   * implementation (e.g. "sonata").
   *
   * @param engine Engine.
   * @param impl Implementation name.
   *
   * @return Provider.
   */
  static Provider create(tl::engine& engine, const std::string& impl,
                         uint16_t provider_id = 0,
                         const std::string &config = std::string(),
                         const tl::pool &pool = tl::pool());

  /**
   * @brief Get the internal configuration as a JSON string.
   *
   * @return The internal configuration.
   */
  std::string getConfig() const override {
    try {
      return self->getConfig();
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Sets a security string that should be provided
   * by Admin RPCs to accept them.
   *
   * @param token Security token to set.
   */
  void setSecurityToken(const std::string &token) override {
    try {
      return self->setSecurityToken(token);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Checks whether the Provider instance is valid.
   */
  operator bool() const override {
    try {
      return self && *self;
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }
};

} // namespace isonata

#endif
