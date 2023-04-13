/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __ISONATA_ASYNC_REQUEST_HPP
#define __ISONATA_ASYNC_REQUEST_HPP

#include <memory>
#include <string>
#include <isonata/Exception.hpp>

namespace isonata {

class AbstractAsyncRequestImpl {

public:

  virtual ~AbstractAsyncRequestImpl() = default;

  virtual void wait() const = 0;

  virtual bool completed() const = 0;

  virtual operator bool() const = 0;
};

/**
 * @brief AsyncRequest objects are used to keep track of
 * on-going asynchronous operations.
 */
class AsyncRequest : public AbstractAsyncRequestImpl {

  std::shared_ptr<AbstractAsyncRequestImpl> self;

public:

  AsyncRequest() = default;
  AsyncRequest(AsyncRequest&&) = default;
  AsyncRequest(const AsyncRequest&) = default;
  AsyncRequest& operator=(AsyncRequest&&) = default;
  AsyncRequest& operator=(const AsyncRequest&) = default;
  ~AsyncRequest() = default;

  /**
   * @brief Wait for the request to complete.
   */
  void wait() const override {
      self->wait();
  }

  /**
   * @brief Test if the request has completed, without blocking.
   */
  bool completed() const override {
      try {
         return self->completed();
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
