/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <thallium.hpp>
#include <isonata/AsyncRequest.hpp>
#include <isonata/Exception.hpp>

namespace isonata {

class YokanCollection;

namespace tl = thallium;

class YokanAsyncRequest : public AbstractAsyncRequestImpl {

  friend class YokanCollection;

  mutable tl::managed<tl::thread> m_ult;

public:

  YokanAsyncRequest(tl::managed<tl::thread> ult)
  : m_ult(std::move(ult))
  {}

  ~YokanAsyncRequest() {}

  void wait() const override {
      m_ult->join();
  }

  bool completed() const override {
      return m_ult->state() == tl::thread_state::terminated;
  }

  operator bool() const override {
      return true;
  }
};


} // namespace isonata
