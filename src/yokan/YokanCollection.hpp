/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Collection.hpp>
#include <isonata/Exception.hpp>
#include "YokanAsyncRequest.hpp"
#include <yokan/cxx/collection.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class YokanCollection : public AbstractCollectionImpl {

  tl::engine        m_engine;
  yokan::Collection m_coll;

public:

  template<typename ... Args>
  YokanCollection(const tl::engine& engine, Args&&... args)
  : m_engine(engine)
  , m_coll(std::forward<Args>(args)...) {}

  ~YokanCollection() = default;

  operator bool() const override {
      return true;
  }

  uint64_t store(const std::string &record, bool commit) const override {
      (void)commit;
      return m_coll.store(record.data(), record.size());
  }

  uint64_t store(const json &record, bool commit) const override {
      return store(record.dump(), commit);
  }

  uint64_t store(const char *record, bool commit) const override {
      (void)commit;
      return m_coll.store(record, strlen(record));
  }

  void store(const std::string &record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
      auto thread = [&record, id, this]() {
        auto i = m_coll.store(record.data(), record.size());
        if(id) *id = i;
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void store(const json &record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
      auto thread = [&record, id, this]() {
        auto record_str = record.dump();
        auto i = m_coll.store(record_str.data(), record_str.size());
        if(id) *id = i;
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void store(const char *record, uint64_t *id, bool commit,
             AsyncRequest *req) const override {
      auto thread = [record, id, this]() {
        auto i = m_coll.store(record, strlen(record));
        if(id) *id = i;
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void store_multi(const std::vector<std::string> &records, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
      auto thread = [&records, ids, this]() {
        const auto n = records.size();
        std::vector<const void*> documents;
        std::vector<size_t>      docsizes;
        documents.reserve(n);
        docsizes.reserve(n);
        for(const auto& r : records) {
            documents.push_back(r.data());
            docsizes.push_back(r.size());
        }
        m_coll.storeMulti(n, documents.data(), docsizes.data(), ids);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void store_multi(const json &records, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
      auto thread = [&records, ids, this]() {
        const auto n = records.size();
        std::vector<std::string> docs;
        std::vector<const void*> documents;
        std::vector<size_t>      docsizes;
        docs.resize(n);
        documents.reserve(n);
        docsizes.reserve(n);
        for(const auto& r : records) {
            docs.push_back(r.dump());
        }
        for(const auto& r : docs) {
            documents.push_back(r.data());
            docsizes.push_back(r.size());
        }
        m_coll.storeMulti(n, documents.data(), docsizes.data(), ids);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void store_multi(const char *const *records, size_t count, uint64_t *ids,
                   bool commit, AsyncRequest *req) const override {
      auto thread = [records, count, ids, this]() {
        std::vector<size_t> docsizes;
        docsizes.reserve(count);
        for(unsigned i = 0; i < count; ++i) {
            docsizes.push_back(strlen(records[i]));
        }
        m_coll.storeMulti(count, (const void* const*)records, docsizes.data(), ids);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void fetch(uint64_t id, std::string *result,
             AsyncRequest *req) const override {
      auto thread = [id, result, this]() {
        size_t size = m_coll.length(id);
        std::string buffer(size, '\0');
        m_coll.load(id, (void*)buffer.data(), &size);
        buffer.resize(size);
        if(result) *result = std::move(buffer);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void fetch(uint64_t id, json *result,
             AsyncRequest *req) const override {
      auto thread = [id, result, this]() {
        size_t size = m_coll.length(id);
        std::string buffer(size, '\0');
        m_coll.load(id, (void*)buffer.data(), &size);
        buffer.resize(size);
        if(result) *result = json::parse(buffer);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void fetch_multi(const uint64_t *ids, size_t count,
                   std::vector<std::string> *result,
                   AsyncRequest *req) const override {
      auto thread = [ids, count, result, this]() {
        std::vector<size_t> sizes(count);
        m_coll.lengthMulti(count, ids, sizes.data());
        std::vector<std::string> buffers(count);
        std::vector<const void*> documents(count);
        for(unsigned i = 0; i < count; ++i) {
            buffers[i].resize(sizes[i]);
            documents[i] = buffers[i].data();
        }
        m_coll.loadMulti(count, ids, (void *const *)documents.data(), sizes.data());
        if(!result) return;
        for(unsigned i = 0; i < count; ++i) {
            buffers[i].resize(sizes[i]);
        }
        *result = std::move(buffers);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void fetch_multi(const uint64_t *ids, size_t count, json *result,
                   AsyncRequest *req) const override {
      auto thread = [ids, count, result, this]() {
        std::vector<size_t> sizes(count);
        m_coll.lengthMulti(count, ids, sizes.data());
        std::vector<std::string> buffers(count);
        std::vector<const void*> documents(count);
        for(unsigned i = 0; i < count; ++i) {
            buffers[i].resize(sizes[i]);
            documents[i] = buffers[i].data();
        }
        m_coll.loadMulti(count, ids, (void *const *)documents.data(), sizes.data());
        if(!result) return;
        *result = json::array();
        for(unsigned i = 0; i < count; ++i) {
            buffers[i].resize(sizes[i]);
            result->push_back(json::parse(buffers[i]));
        }
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
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

  void update(uint64_t id, const std::string &record, bool commit,
              AsyncRequest *req) const override {
      (void)commit;
      auto thread = [id, &record, this]() {
          m_coll.update(id, (void*)record.data(), record.size());
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void update(uint64_t id, const json &record, bool commit,
              AsyncRequest *req) const override {
      (void)commit;
      auto thread = [id, &record, this]() {
          auto record_str = record.dump();
          m_coll.update(id, (void*)record_str.data(), record_str.size());
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void update(uint64_t id, const char *record, bool commit,
              AsyncRequest *req) const override {
      (void)commit;
      auto thread = [id, record, this]() {
          m_coll.update(id, (void*)record, strlen(record));
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void update_multi(const uint64_t *ids, const json &records,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
      (void)commit;
      auto thread = [ids, &records, updated, this]() {
          auto n = records.size();
          std::vector<std::string> docs(n);
          std::vector<const void*> docsPtr(n);
          std::vector<size_t> docSizes(n);
          for(unsigned i = 0; i < n; ++i) {
            docs[i] = records[i].dump();
            docsPtr[i] = docs[i].data();
            docSizes[i] = docs[i].size();
          }
          m_coll.updateMulti(n, ids, (const void *const*)docsPtr.data(), docSizes.data());
          if(!updated) return;
          updated->resize(n);
          for(unsigned i = 0; i < n; ++i) {
              (*updated)[i] = true;
          }
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void update_multi(const uint64_t *ids,
                    const std::vector<std::string> &records,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
      (void)commit;
      auto thread = [ids, &records, updated, this]() {
          auto n = records.size();
          std::vector<const void*> docsPtr(n);
          std::vector<size_t> docSizes(n);
          for(unsigned i = 0; i < n; ++i) {
            docsPtr[i] = records[i].data();
            docSizes[i] = records[i].size();
          }
          m_coll.updateMulti(n, ids, (const void *const*)docsPtr.data(), docSizes.data());
          if(!updated) return;
          updated->resize(n);
          for(unsigned i = 0; i < n; ++i) {
              (*updated)[i] = true;
          }
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void update_multi(uint64_t *ids, const char *const *records, size_t count,
                    std::vector<bool> *updated, bool commit,
                    AsyncRequest *req) const override {
      (void)commit;
      auto thread = [ids, records, count, updated, this]() {
          auto n = count;
          std::vector<const void*> docsPtr(n);
          std::vector<size_t> docSizes(n);
          for(unsigned i = 0; i < n; ++i) {
            docsPtr[i] = records[i];
            docSizes[i] = strlen(records[i]);
          }
          m_coll.updateMulti(n, ids, (const void *const*)docsPtr.data(), docSizes.data());
          if(!updated) return;
          updated->resize(n);
          for(unsigned i = 0; i < n; ++i) {
              (*updated)[i] = true;
          }
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
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
      return m_coll.last_id();
  }

  size_t size() const override {
      return m_coll.size();
  }

  void erase(uint64_t id, bool commit,
             AsyncRequest *req) const override {
      (void)commit;
      auto thread = [id, this]() {
        m_coll.erase(id);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }

  void erase_multi(const uint64_t *ids, size_t size, bool commit,
                   AsyncRequest *req) const override {
      (void)commit;
      auto thread = [ids, size, this]() {
        m_coll.eraseMulti(size, ids);
      };
      if(!req) thread();
      else {
        auto ult = m_engine.get_progress_pool().make_thread(std::move(thread));
        tl::thread::yield_to(*ult);
        *req = AsyncRequest{std::make_shared<YokanAsyncRequest>(std::move(ult))};
      }
  }
};

} // namespace isonata
