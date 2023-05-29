/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "SonataCollection.hpp"
#include <isonata/Database.hpp>
#include <sonata/Database.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class SonataDatabase : public AbstractDatabaseImpl {

  sonata::Database db;

public:

  SonataDatabase(sonata::Database d)
  : db(std::move(d)) {}

  ~SonataDatabase() {}

  Collection create(const std::string &collectionName) const override {
    return Collection{std::make_shared<SonataCollection>(db.create(collectionName))};
  }

  bool exists(const std::string &collectionName) const override {
    return db.exists(collectionName);
  }

  Collection open(const std::string &collectionName, bool check) const override {
    return Collection{std::make_shared<SonataCollection>(db.open(collectionName, check))};
  }

  void drop(const std::string &collectionName) const override {
    db.drop(collectionName);
  }

  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars,
        std::unordered_map<std::string, std::string> *result,
        bool commit) const override {
    db.execute(code, vars, result, commit);
  }

  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars, json *result,
        bool commit) const override {
    db.execute(code, vars, result, commit);
  }

  void commit() const override {
    db.commit();
  }

  operator bool() const override {
    return db;
  }
};


} // namespace isonata
