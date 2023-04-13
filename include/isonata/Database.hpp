/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __ISONATA_DATABASE_HPP
#define __ISONATA_DATABASE_HPP

#include <isonata/Collection.hpp>
#include <isonata/Exception.hpp>
#include <thallium.hpp>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class Client;

class AbstractDatabaseImpl {

public:

  virtual ~AbstractDatabaseImpl() = default;

  virtual Collection create(const std::string &collectionName) const = 0;

  virtual bool exists(const std::string &collectionName) const = 0;

  virtual Collection open(const std::string &collectionName, bool check = true) const = 0;

  virtual void drop(const std::string &collectionName) const = 0;

  virtual void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars,
        std::unordered_map<std::string, std::string> *result,
        bool commit) const = 0;

  virtual void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars, json *result,
        bool commit) const = 0;

  virtual void commit() const = 0;

  virtual operator bool() const = 0;
};

/**
 * @brief A Database object is a handle for a remote database
 * on a server. It enables creating and opening collections.
 */
class Database : public AbstractDatabaseImpl {

  std::shared_ptr<AbstractDatabaseImpl> self;

public:

  Database() = default;
  Database(Database&&) = default;
  Database(const Database&) = default;
  Database& operator=(Database&&) = default;
  Database& operator=(const Database&) = default;
  ~Database() = default;

  /**
   * @brief Creates a collection.
   *
   * @param collectionName Name of the collection to create.
   *
   * @return A valid Collection instance pointing to the new collection.
   */
  Collection create(const std::string &collectionName) const override {
    try {
      return self->create(collectionName);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Checks if a collection exists.
   *
   * @param collectionName Name of the collection.
   *
   * @return true if the collection exists, false otherwise.
   */
  bool exists(const std::string &collectionName) const override {
    try {
      return self->exists(collectionName);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Opens the specified collection. If "check" is set to true,
   * an RPC will be issued to check that the collection exists. The
   * function will throw an exception if it does not. You may set "check"
   * to false if you know for sure that the collection exists.
   *
   * @param collectionName Name of the collection.
   * @param check Checks if the Collection exists by issuing an RPC.
   *
   * @return A valid Collection instance pointing to the collection.
   */
  Collection open(const std::string &collectionName, bool check = true) const override {
    try {
      return self->open(collectionName, check);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Destroys the collection. The collection must exist.
   *
   * @param collectionName Name of the collection.
   */
  void drop(const std::string &collectionName) const override {
    try {
      return self->drop(collectionName);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Sends a code to execute on the database. The output
   * set indicates which variables should then be extracted and
   * returned.
   *
   * @param code Code to send to execute on the database.
   * @param vars Set of variables to extract after execution.
   * @param result Resuling map from variable names to their content.
   * @param commit Whether to commit changes to storage.
   */
  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars,
        std::unordered_map<std::string, std::string> *result,
        bool commit = false) const override {
    try {
      return self->execute(code, vars, result, commit);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Sends a code to execute on the database. The output
   * set indicates which variables should then be extracted and
   * returned.
   *
   * @param code Code to send to execute on the database.
   * @param vars Set of variables to extract after execution.
   * @param result Resuling JSON object containing a mapping from
   *        variable names to their content.
   * @param commit Whether to commit changes to storage.
   */
  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars, json *result,
        bool commit = false) const override {
    try {
      return self->execute(code, vars, result, commit);
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Commit any changes made to the database.
   */
  void commit() const override {
    try {
      self->commit();
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }

  /**
   * @brief Checks if the Database instance is valid.
   */
  operator bool() const override {
    try {
      return self && *self;
    } catch(const std::exception& ex) { throw Exception(ex.what()); }
  }
};

} // namespace isonata

#endif
