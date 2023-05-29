/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "YokanDatabase.hpp"
#include <isonata/Client.hpp>
#include <isonata/Exception.hpp>

namespace isonata {

class YokanClient : public AbstractClientImpl {

public:

  template<typename ... Args>
  YokanClient(Args&&... args) {}

  ~YokanClient() {}

  const thallium::engine &engine() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  Database open(
        const std::string &address, uint16_t provider_id,
        const std::string &db_name, bool check) const {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  Database open(
        const ProviderHandle &ph, const std::string &db_name,
        bool check) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  ProviderHandle createProviderHandle(
        const std::string &address, uint16_t provider_id) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  ProviderHandle createProviderHandle(
        hg_addr_t address, uint16_t provider_id) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  operator bool() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }
};

} // namespace isonata
