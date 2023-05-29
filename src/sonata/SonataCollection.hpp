/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Collection.hpp>
#include <sonata/Collection.hpp>
#include "SonataAsyncRequest.hpp"

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class SonataCollection : public AbstractCollectionImpl {

  sonata::Collection coll;

public:

  SonataCollection(sonata::Collection c)
  : coll(std::move(c)) {}

  ~SonataCollection() {}

  operator bool() const override {
    return coll;
  }

  uint64_t store(const std::string &record, bool commit) const override {
    return coll.store(record, commit);
  }

  uint64_t store(const json &record, bool commit) const override {
    return coll.store(record, commit);
  }

  uint64_t store(const char *record, bool commit) const override {
    return coll.store(record, commit);
  }

  void store(const std::string &record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.store(record, id, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.store(record, id, commit);
    }
  }

  void store(const json &record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.store(record, id, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.store(record, id, commit);
    }
  }

  void store(const char *record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.store(record, id, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.store(record, id, commit);
    }
  }

  void store_multi(const std::vector<std::string> &records, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.store_multi(records, ids, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.store_multi(records, ids, commit);
    }
  }

  void store_multi(const json &records, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.store_multi(records, ids, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.store_multi(records, ids, commit);
    }
  }

  void store_multi(const char *const *records, size_t count, uint64_t *ids,
                   bool commit, AsyncRequest *req) const {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.store_multi(records, count, ids, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.store_multi(records, count, ids, commit);
    }
  }

  void fetch(uint64_t id, std::string *result,
             AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.fetch(id, result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.fetch(id, result);
    }
  }

  void fetch(uint64_t id, json *result,
             AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.fetch(id, result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.fetch(id, result);
    }
  }

  void fetch_multi(const uint64_t *ids, size_t count,
                   std::vector<std::string> *result,
                   AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.fetch_multi(ids, count, result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.fetch_multi(ids, count, result);
    }
  }

  void fetch_multi(const uint64_t *id, size_t count, json *result,
                   AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.fetch_multi(id, count, result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.fetch_multi(id, count, result);
    }
  }

  void filter(const std::string &filterCode, std::vector<std::string> *result,
              AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.filter(filterCode, result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.filter(filterCode, result);
    }
  }

  void filter(const std::string &filterCode, json *result,
              AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.filter(filterCode, result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.filter(filterCode, result);
    }
  }

  void update(uint64_t id, const json &record, bool commit,
              AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.update(id, record, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.update(id, record, commit);
    }
  }

  void update(uint64_t id, const std::string &record, bool commit,
              AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.update(id, record, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.update(id, record, commit);
    }
  }

  void update(uint64_t id, const char *record, bool commit,
              AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.update(id, record, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.update(id, record, commit);
    }
  }

  void update_multi(const uint64_t *ids, const json &record,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.update_multi(ids, record, updated, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.update_multi(ids, record, updated, commit);
    }
  }

  void update_multi(const uint64_t *ids,
                    const std::vector<std::string> &records,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.update_multi(ids, records, updated, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.update_multi(ids, records, updated, commit);
    }
  }

  void update_multi(uint64_t *ids, const char *const *records, size_t count,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.update_multi(ids, records, count, updated, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.update_multi(ids, records, count, updated, commit);
    }
  }

  void all(std::vector<std::string> *result, AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.all(result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.all(result);
    }
  }

  void all(json *result, AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.all(result, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.all(result);
    }
  }

  uint64_t last_record_id() const override {
    return coll.last_record_id();
  }

  size_t size() const override {
    return coll.size();
  }

  void erase(uint64_t id, bool commit,
             AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.erase(id, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.erase(id, commit);
    }
  }

  void erase_multi(const uint64_t *ids, size_t size, bool commit,
                   AsyncRequest *req) const override {
    if(req) {
        auto preq = std::make_shared<SonataAsyncRequest>();
        coll.erase_multi(ids, size, commit, &preq->req);
        *req = AsyncRequest{std::move(preq)};
    } else {
        coll.erase_multi(ids, size, commit);
    }
  }
};

} // namespace isonata
