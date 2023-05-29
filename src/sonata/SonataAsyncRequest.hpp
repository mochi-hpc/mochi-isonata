/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/AsyncRequest.hpp>
#include <sonata/AsyncRequest.hpp>

namespace isonata {

class SonataCollection;

class SonataAsyncRequest : public AbstractAsyncRequestImpl {

  friend class SonataCollection;

  sonata::AsyncRequest req;

public:

  SonataAsyncRequest(sonata::AsyncRequest r = sonata::AsyncRequest{})
  : req(std::move(r)) {}

  ~SonataAsyncRequest() {}

  void wait() const override {
    req.wait();
  }

  bool completed() const override {
    return req.completed();
  }

  operator bool() const override {
    return req;
  }
};


} // namespace isonata
