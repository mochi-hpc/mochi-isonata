/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Provider.hpp>
#include <isonata/Exception.hpp>
#include <yokan/cxx/server.hpp>

namespace isonata {

namespace tl = thallium;

class YokanProvider : public AbstractProviderImpl {

  yokan::Provider m_provider;

public:

  template<typename ... Args>
  YokanProvider(Args&&... args)
  : m_provider{std::forward<Args>(args)...} {}

  virtual ~YokanProvider() = default;

  std::string getConfig() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void setSecurityToken(const std::string &token) override {
      throw Exception{"Yokan does not support security tokens"};
  }

  operator bool() const override {
      return true;
  }
};
} // namespace isonata
