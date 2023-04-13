/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Admin.hpp>
#include <isonata/Provider.hpp>
#include <isonata/Client.hpp>
#include <isonata/Collection.hpp>
#include <isonata/Database.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>

using json = nlohmann::json;

static const std::string resource_type = "unqlite";
static constexpr const char* resource_config = "{ \"path\" : \"mydb\" }";

TEST_CASE("Client tests", "[client]") {

    auto engine = thallium::engine("na+sm", THALLIUM_SERVER_MODE);
    // Initialize the Sonata provider
    isonata::Provider provider = isonata::Provider::create(engine, "sonata");

    // Create an admin
    isonata::Admin admin = isonata::Admin::create(engine, "sonata");
    std::string addr = engine.self();

    // Create a database
    admin.createDatabase(addr, 0, "mydb", resource_type, resource_config);

    SECTION("Create client") {

      isonata::Client client = isonata::Client::create(engine, "sonata");

      SECTION("Open database") {

        auto db = client.open(addr, 0, "mydb");

        SECTION("Access collection") {
            auto coll = db.create("mycollection");

            coll.store("{\"name\":\"Matthieu\"}");
            coll.store("{\"name\":\"Rob\"}");
            coll.store("{\"name\":\"Phil\"}");

            REQUIRE(coll.size() == 3);
            REQUIRE(coll.last_record_id() == 2);

            json record;
            coll.fetch(1, &record);

            REQUIRE(record.contains("name"));
            REQUIRE(record["name"] == "Rob");
        }

      }

    }

    // Destroy the database
    admin.destroyDatabase(addr, 0, "mydb");

    // Finalize the engine
    engine.finalize();
}
