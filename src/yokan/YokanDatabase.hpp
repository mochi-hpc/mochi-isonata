/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "YokanCollection.hpp"
#include <isonata/Database.hpp>
#include <isonata/Exception.hpp>

namespace isonata {

namespace tl = thallium;
using nlohmann::json;

class YokanDatabase : public AbstractDatabaseImpl {

public:

  YokanDatabase() {}

  ~YokanDatabase() {}

  Collection create(const std::string &collectionName) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  bool exists(const std::string &collectionName) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  Collection open(const std::string &collectionName, bool check) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void drop(const std::string &collectionName) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars,
        std::unordered_map<std::string, std::string> *result,
        bool commit) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void execute(
        const std::string &code,
        const std::unordered_set<std::string> &vars, json *result,
        bool commit) const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  void commit() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }

  operator bool() const override {
      // TODO
      throw Exception{std::string{"Function "} + __PRETTY_FUNCTION__ + " is not implemented"};
  }
};


} // namespace isonata
