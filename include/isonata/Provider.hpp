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

namespace isonata {

namespace tl = thallium;

/**
 * @brief A Provider is an object that can receive RPCs
 * and dispatch them to specific databases.
 */
class AbstractProviderImpl {

public:

  virtual std::string getConfig() const = 0;

  virtual void setSecurityToken(const std::string &token) = 0;

  virtual operator bool() const = 0;
};

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
  static Provider create(const tl::engine& engine, const std::string& impl);

  /**
   * @brief Get the internal configuration as a JSON string.
   *
   * @return The internal configuration.
   */
  std::string getConfig() const override {
    return self->getConfig();
  }

  /**
   * @brief Sets a security string that should be provided
   * by Admin RPCs to accept them.
   *
   * @param token Security token to set.
   */
  void setSecurityToken(const std::string &token) override {
    return self->setSecurityToken(token);
  }

  /**
   * @brief Checks whether the Provider instance is valid.
   */
  operator bool() const override {
    return self && *self;
  }
};

} // namespace isonata

#endif
