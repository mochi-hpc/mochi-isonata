/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Provider.hpp>
#include <sonata/Provider.hpp>

namespace isonata {

namespace tl = thallium;

class SonataProvider : public AbstractProviderImpl {

  sonata::Provider provider;

public:

  template<typename ... Args>
  SonataProvider(Args&&... args)
  : provider(std::forward<Args>(args)...) {}

  virtual ~SonataProvider() = default;

  std::string getConfig() const override {
    return provider.getConfig();
  }

  void setSecurityToken(const std::string &token) override {
    return provider.setSecurityToken(token);
  }

  operator bool() const override {
    return provider;
  }
};
} // namespace isonata
