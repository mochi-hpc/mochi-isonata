/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Collection.hpp>
#include <isonata/Exception.hpp>
#include "YokanAsyncRequest.hpp"

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class YokanCollection : public AbstractCollectionImpl {

public:

  YokanCollection() {}

  ~YokanCollection() {}

  operator bool() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  uint64_t store(const std::string &record, bool commit) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  uint64_t store(const json &record, bool commit) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  uint64_t store(const char *record, bool commit) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void store(const std::string &record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void store(const json &record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void store(const char *record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void store_multi(const std::vector<std::string> &records, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void store_multi(const json &records, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void store_multi(const char *const *records, size_t count, uint64_t *ids,
                   bool commit, AsyncRequest *req) const {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void fetch(uint64_t id, std::string *result,
             AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void fetch(uint64_t id, json *result,
             AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void fetch_multi(const uint64_t *ids, size_t count,
                   std::vector<std::string> *result,
                   AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void fetch_multi(const uint64_t *id, size_t count, json *result,
                   AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void filter(const std::string &filterCode, std::vector<std::string> *result,
              AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void filter(const std::string &filterCode, json *result,
              AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void update(uint64_t id, const json &record, bool commit,
              AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void update(uint64_t id, const std::string &record, bool commit,
              AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void update(uint64_t id, const char *record, bool commit,
              AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void update_multi(const uint64_t *ids, const json &record,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void update_multi(const uint64_t *ids,
                    const std::vector<std::string> &records,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void update_multi(uint64_t *ids, const char *const *records, size_t count,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void all(std::vector<std::string> *result, AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void all(json *result, AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  uint64_t last_record_id() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  size_t size() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void erase(uint64_t id, bool commit,
             AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void erase_multi(const uint64_t *ids, size_t size, bool commit,
                   AsyncRequest *req) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }
};

} // namespace isonata
