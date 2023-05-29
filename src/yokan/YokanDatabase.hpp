/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "YokanCollection.hpp"
#include <isonata/Database.hpp>
#include <isonata/Exception.hpp>
#include <yokan/cxx/database.hpp>
#include <yokan/cxx/collection.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class YokanDatabase : public AbstractDatabaseImpl {

  tl::engine      m_engine;
  yokan::Database m_db;

public:

  YokanDatabase(const tl::engine& engine, yokan::Database db)
  : m_engine(engine)
  , m_db(std::move(db)) {}

  ~YokanDatabase() {}

  Collection create(const std::string &collectionName) const override {
      m_db.createCollection(collectionName.c_str());
      auto coll = std::make_shared<YokanCollection>(m_engine, collectionName.c_str(), m_db);
      return Collection{coll};
  }

  bool exists(const std::string &collectionName) const override {
      return m_db.collectionExists(collectionName.c_str());
  }

  Collection open(const std::string &collectionName, bool check) const override {
      if(!exists(collectionName))
          throw Exception(std::string{"Collection "} + collectionName + " does not exist");
      auto coll = std::make_shared<YokanCollection>(m_engine, collectionName.c_str(), m_db);
      return Collection{coll};
  }

  void drop(const std::string &collectionName) const override {
      m_db.dropCollection(collectionName.c_str());
  }

  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars,
        std::unordered_map<std::string, std::string> *result,
        bool commit) const override {
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars, json *result,
        bool commit) const override {
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void commit() const override {}

  operator bool() const override {
      return true;
  }
};


} // namespace isonata
