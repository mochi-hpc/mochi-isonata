/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/AsyncRequest.hpp>
#include <isonata/Exception.hpp>

namespace isonata {

class YokanCollection;

class YokanAsyncRequest : public AbstractAsyncRequestImpl {

  friend class YokanCollection;

public:

  YokanAsyncRequest()
  {
      // TODO
  }

  ~YokanAsyncRequest() {}

  void wait() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  bool completed() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  operator bool() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }
};


} // namespace isonata
