/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __ISONATA_COLLECTION_HPP
#define __ISONATA_COLLECTION_HPP

#include <isonata/AsyncRequest.hpp>
#include <isonata/Exception.hpp>
#include <thallium.hpp>
#include <nlohmann/json.hpp>
#include <memory>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class Database;

class AbstractCollectionImpl {

public:

  virtual ~AbstractCollectionImpl() = default;

  virtual operator bool() const = 0;

  virtual uint64_t store(const std::string &record, bool commit) const {
    uint64_t record_id;
    store(record, &record_id, commit, nullptr);
    return record_id;
  }

  virtual uint64_t store(const json &record, bool commit) const {
    uint64_t record_id;
    store(record, &record_id, commit, nullptr);
    return record_id;
  }

  virtual uint64_t store(const char *record, bool commit) const {
    uint64_t record_id;
    store(record, &record_id, commit, nullptr);
    return record_id;
  }

  virtual void store(const std::string &record, uint64_t *id, bool commit,
                     AsyncRequest *req) const = 0;

  virtual void store(const json &record, uint64_t *id, bool commit,
                     AsyncRequest *req) const {
    store(record.dump(), id, commit, req);
  }

  virtual void store(const char *record, uint64_t *id, bool commit,
                     AsyncRequest *req) const {
    store(std::string(record), id, commit, req);
  }

  virtual void store_multi(const std::vector<std::string> &records, uint64_t *ids,
                           bool commit, AsyncRequest *req) const = 0;

  virtual void store_multi(
        const json &records, uint64_t *ids,
        bool commit, AsyncRequest *req) const {
      if (records.type() != json::value_t::array) {
          throw Exception("JSON object is not of Array type");
      }
      store_multi(records.dump(), ids, commit, req);
  }

  virtual void store_multi(const char *const *records, size_t count, uint64_t *ids,
                           bool commit, AsyncRequest *req) const {
    std::vector<std::string> vec;
    vec.reserve(count);
    for (size_t i = 0; i < count; i++) {
      vec.emplace_back(records[i]);
    }
    store_multi(vec, ids, commit, req);
  }

  virtual void fetch(uint64_t id, std::string *result,
                     AsyncRequest *req) const = 0;

  virtual void fetch(uint64_t id, json *result,
                     AsyncRequest *req) const = 0;

  virtual void fetch_multi(const uint64_t *ids, size_t count,
                           std::vector<std::string> *result,
                           AsyncRequest *req) const = 0;

  virtual void fetch_multi(const uint64_t *id, size_t count, json *result,
                           AsyncRequest *req) const = 0;

  virtual void filter(const std::string &filterCode, std::vector<std::string> *result,
                      AsyncRequest *req) const = 0;

  virtual void filter(const std::string &filterCode, json *result,
                      AsyncRequest *req) const = 0;

  virtual void update(uint64_t id, const json &record, bool commit,
                      AsyncRequest *req) const = 0;

  virtual void update(uint64_t id, const std::string &record, bool commit,
                      AsyncRequest *req) const = 0;

  virtual void update(uint64_t id, const char *record, bool commit,
              AsyncRequest *req) const {
    return update(id, std::string(record), commit, req);
  }

  virtual void update_multi(const uint64_t *id, const json &record,
                            std::vector<bool> *updated, bool commit,
                            AsyncRequest *req) const = 0;

  virtual void update_multi(const uint64_t *ids,
                            const std::vector<std::string> &records,
                            std::vector<bool> *updated, bool commit,
                            AsyncRequest *req) const = 0;

  virtual void update_multi(uint64_t *ids, const char *const *records, size_t count,
                            std::vector<bool> *updated, bool commit,
                            AsyncRequest *req) const {
    std::vector<std::string> vec;
    vec.reserve(count);
    for (size_t i = 0; i < count; i++) {
      vec.emplace_back(records[i]);
    }
    return update_multi(ids, vec, updated, commit, req);
  }

  virtual void all(std::vector<std::string> *result, AsyncRequest *req) const = 0;

  virtual void all(json *result, AsyncRequest *req) const = 0;

  virtual uint64_t last_record_id() const = 0;

  virtual size_t size() const = 0;

  virtual void erase(uint64_t id, bool commit,
                     AsyncRequest *req) const = 0;

  virtual void erase_multi(const uint64_t *ids, size_t size, bool commit,
                           AsyncRequest *req) const = 0;
};

/**
 * @brief The Collection object is a handle to a collection
 * in a given remote database on a server. It offers function
 * to store and search documents.
 */
class Collection : public AbstractCollectionImpl {

  std::shared_ptr<AbstractCollectionImpl> self;

public:

  /**
   * @brief Checks if the object is valid.
   */
  operator bool() const override {
    return self && *self;
  }

  /**
   * @brief Stores a document into the collection.
   *
   * @param record A valid JSON-formated document.
   * @param commit Whether to commit the change to storage.
   *
   * @return the record id of the stored document.
   */
  uint64_t store(const std::string &record, bool commit = false) const override {
    return self->store(record, commit);
  }

  /**
   * @brief Stores a document into the collection.
   *
   * @param record A JSON object.
   * @param commit Whether to commit the change to storage.
   *
   * @return the record id of the stored document.
   */
  uint64_t store(const json &record, bool commit = false) const override {
    return self->store(record, commit);
  }

  /**
   * @brief Stores a document into the collection.
   *
   * @param record A valid JSON-formated document.
   * @param commit Whether to commit the change to storage.
   *
   * @return the record id of the stored document.
   */
  uint64_t store(const char *record, bool commit = false) const override {
    return self->store(record, commit);
  }

  /**
   * @brief Asynchronously stores a document into the collection.
   * If the pointer to the request is null, this function will be
   * executed synchronously.
   *
   * @param record A valid JSON-formated document.
   * @param id Pointer to a record id set when the request completes.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   *
   * @return the record id of the stored document.
   */
  void store(const std::string &record, uint64_t *id, bool commit = false,
             AsyncRequest *req = nullptr) const override {
    return self->store(record, id, commit, req);
  }

  /**
   * @brief Asynchronously stores a document into the collection.
   * If the pointer to the request is null, this function will be
   * executed synchronously.
   *
   * @param record A JSON document.
   * @param id Pointer to a record id set when the request completes.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   *
   * @return the record id of the stored document.
   */
  void store(const json &record, uint64_t *id, bool commit = false,
                     AsyncRequest *req = nullptr) const override {
    return self->store(record, id, commit, req);
  }

  /**
   * @brief Asynchronously stores a document into the collection.
   * If the pointer to the request is null, this function will be
   * executed synchronously.
   *
   * @param record A valid JSON-formated document.
   * @param id Pointer to a record id set when the request completes.
   * @param req Pointer to a request to wait on.
   *
   * @return the record id of the stored document.
   */
  void store(const char *record, uint64_t *id, bool commit = false,
             AsyncRequest *req = nullptr) const override {
    return self->store(record, id, commit, req);
  }

  /**
   * @brief Stores multiple records in the collection. Each string
   * in the vector should be a valid JSON object. The ids parameter
   * should be a pointer to a memory region sufficiently large to
   * store the resulting records.size() identifiers.
   *
   * This function will either store all or none of the records.
   *
   * @param records Vector of records to store.
   * @param ids Resulting ids.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void store_multi(const std::vector<std::string> &records, uint64_t *ids,
                   bool commit = false, AsyncRequest *req = nullptr) const override {
    return self->store_multi(records, ids, commit, req);
  }

  /**
   * @brief Stores multiple records in the collection. The provided
   * json should be an array of objects. The ids parameter
   * should be a pointer to a memory region sufficiently large to
   * store the resulting records.size() identifiers.
   *
   * This function will either store all or none of the records.
   *
   * @param records JSON array of records to store.
   * @param ids Resulting ids.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void store_multi(
        const json &records, uint64_t *ids,
        bool commit = false, AsyncRequest *req = nullptr) const override {
      self->store_multi(records, ids, commit, req);
  }

  /**
   * @brief Stores multiple records in the collection. Each null-terminated
   * string in the array should be a valid JSON object. The ids parameter
   * should be a pointer to a memory region sufficiently large to store the
   * resulting count identifiers.
   *
   * This function will either store all or none of the records.
   *
   * @param records Vector of records to store.
   * @param count Number of records to store.
   * @param ids Resulting ids.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void store_multi(const char *const *records, size_t count, uint64_t *ids,
                   bool commit = false, AsyncRequest *req = nullptr) const override {
    self->store_multi(records, count, ids, commit, req);
  }

  /**
   * @brief Asynchronously fetches a document by its record id.
   * If req is null, this function becomes synchronous.
   *
   * @param[in] id Record id.
   * @param[out] result Resulting string.
   * @param req Pointer to a request to wait on.
   */
  void fetch(uint64_t id, std::string *result,
             AsyncRequest *req = nullptr) const override {
    self->fetch(id, result, req);
  }

  /**
   * @brief Asynchronously fetches a document by its record id.
   * If req is null, this function becomes synchronous.
   *
   * @param[in] id Record id.
   * @param[out] result Resulting JSON object.
   * @param req Pointer to a request to wait on.
   */
  void fetch(uint64_t id, json *result,
             AsyncRequest *req = nullptr) const override {
    self->fetch(id, result, req);
  }

  /**
   * @brief Asynchronously fetches multiple documents by their record id.
   * If req is null, this function becomes synchronous.
   *
   * @param[in] ids Array of record ids.
   * @param[in] count Number of records.
   * @param[out] result Resulting string.
   * @param req Pointer to a request to wait on.
   */
  void fetch_multi(const uint64_t *ids, size_t count,
                   std::vector<std::string> *result,
                   AsyncRequest *req = nullptr) const override {
    self->fetch_multi(ids, count, result, req);
  }

  /**
   * @brief Asynchronously fetches a document by its record id.
   * If req is null, this function becomes synchronous.
   *
   * @param[in] ids Record ids.
   * @param[in] count Number of records to fetch.
   * @param[out] result Resulting JSON array.
   * @param req Pointer to a request to wait on.
   */
  void fetch_multi(const uint64_t *id, size_t count, json *result,
                   AsyncRequest *req = nullptr) const override {
    self->fetch_multi(id, count, result, req);
  }

  /**
   * @brief Asynchronously filters the collection and returns the
   * records that match the condition. This condition should
   * be expressed as a Jx9 function returning TRUE or FALSE.
   * For example the following Jx9 function selects only
   * the records where x < 4 :
   *
   * "function($record) { return $record.x < 4; }"
   *
   * If req is null, this function becomes synchronous.
   *
   * @param filterCode A Jx9 filter code.
   * @param result Resuling vector of records as strings.
   * @param req Pointer to a request to wait on.
   */
  void filter(const std::string &filterCode, std::vector<std::string> *result,
              AsyncRequest *req = nullptr) const override {
    self->filter(filterCode, result, req);
  }

  /**
   * @brief Asynchronously filters the collection and returns the
   * records that match the condition. This condition should
   * be expressed as a Jx9 function returning TRUE or FALSE.
   * For example the following Jx9 function selects only
   * the records where x < 4 :
   *
   * "function($record) { return $record.x < 4; }"
   *
   * If req is null, this function becomes synchronous.
   *
   * @param filterCode A Jx9 filter code.
   * @param result Resuling JSON object containing the array of results.
   * @param req Pointer to a request to wait on.
   */
  void filter(const std::string &filterCode, json *result,
              AsyncRequest *req = nullptr) const override {
    self->filter(filterCode, result, req);
  }

  /**
   * @brief Asynchronously updates the content of a document with a new content.
   * If req is null, this function becomes synchronous.
   *
   * @param id Record id of the document to update.
   * @param record New document.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void update(uint64_t id, const json &record, bool commit = false,
              AsyncRequest *req = nullptr) const override {
    self->update(id, record, commit, req);
  }

  /**
   * @brief Asynchronously updates the content of a document with a new content.
   * If req is null, this function becomes synchronous.
   *
   * @param id Record id of the document to update.
   * @param record New document.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void update(uint64_t id, const std::string &record, bool commit = false,
              AsyncRequest *req = nullptr) const override {
    self->update(id, record, commit, req);
  }

  /**
   * @brief Asynchronously updates the content of a document with a new content.
   * If req is null, this function becomes synchronous.
   *
   * @param id Record id of the document to update.
   * @param record New document.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void update(uint64_t id, const char *record, bool commit = false,
              AsyncRequest *req = nullptr) const override {
    self->update(id, record, commit, req);
  }

  /**
   * @brief Asynchronously updates the content of multipl documents with
   * new contents. If req is null, this function becomes synchronous.
   * The provided JSON value should be an array.
   *
   * @param ids Record ids of the documents to update.
   * @param records New documents.
   * @param updated Pointer to a vector that will contain whether
   *                each record was updated.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void update_multi(const uint64_t *id, const json &record,
                    std::vector<bool> *updated, bool commit = false,
                    AsyncRequest *req = nullptr) const override {
    self->update_multi(id, record, updated, commit, req);
  }

  /**
   * @brief Asynchronously updates the content of multiple documents with
   * new contents. If req is null, this function becomes synchronous.
   *
   * @param ids Record ids of the documents to update.
   * @param record New document.
   * @param updated Pointer to a vector that will contain whether
   *                each record was updated.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void update_multi(const uint64_t *ids,
                    const std::vector<std::string> &records,
                    std::vector<bool> *updated, bool commit = false,
                    AsyncRequest *req = nullptr) const override {
    self->update_multi(ids, records, updated, commit, req);
  }

  /**
   * @brief Asynchronously updates the content of multiple documents with
   * new contents. If req is null, this function becomes synchronous.
   *
   * @param ids Record ids of the documents to update.
   * @param records New documents (as C array of null-terminated strings).
   * @param count Number of documents to update.
   * @param updated Pointer to a vector that will contain whether
   *                each record was updated.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void update_multi(uint64_t *ids, const char *const *records, size_t count,
                            std::vector<bool> *updated, bool commit = false,
                            AsyncRequest *req = nullptr) const override {
    self->update_multi(ids, records, count, updated, commit, req);
  }

  /**
   * @brief Asynchronously returns all the documents from the collection
   * as a vector of strings.
   * If req is null, this function becomes synchronous.
   *
   * @param result All the documents from the collection.
   * @param req Pointer to a request to wait on.
   */
  void all(std::vector<std::string> *result, AsyncRequest *req = nullptr) const override {
    self->all(result, req);
  }

  /**
   * @brief Asynchronously returns all the documents from the collection
   * as a JSON object.
   * If req is null, this function becomes synchronous.
   *
   * @param result All the documents from the collection.
   * @param req Pointer to a request to wait on.
   */
  void all(json *result, AsyncRequest *req = nullptr) const override {
    self->all(result, req);
  }

  /**
   * @brief Returns the last record id used by the collection.
   *
   * @return The last record id.
   * @param req Pointer to a request to wait on.
   */
  uint64_t last_record_id() const override {
    return self->last_record_id();
  }

  /**
   * @brief Returns the number of documents stored in the
   * collection.
   *
   * @return The size of the collection.
   */
  size_t size() const override {
    return self->size();
  }

  /**
   * @brief Asynchronously erases a document from the collection.
   * If req is null, this function becomes synchronous.
   *
   * @param id Record id of the document to erase.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void erase(uint64_t id, bool commit = false,
             AsyncRequest *req = nullptr) const override {
    return self->erase(id, commit, req);
  }

  /**
   * @brief Asynchronously erases multiple documents from the collection.
   * If req is null, this function becomes synchronous.
   *
   * @param ids Record ids of the documents to erase.
   * @param commit Whether to commit the changes to storage.
   * @param req Pointer to a request to wait on.
   */
  void erase_multi(const uint64_t *ids, size_t size, bool commit = false,
                   AsyncRequest *req = nullptr) const override {
    return self->erase_multi(ids, size, commit, req);
  }
};
} // namespace isonata

#endif
