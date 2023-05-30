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
#include <catch2/generators/catch_generators.hpp>

using namespace Catch::Generators;


using json = nlohmann::json;

static const std::string resource_type = "unqlite";
static constexpr const char* resource_config = "{ \"path\" : \"mydb\", \"mode\":\"create\" }";

TEST_CASE("Client tests", "[client]") {

    auto backend = GENERATE(as<std::string>{}, "yokan");//, "sonata");

    auto engine = thallium::engine("na+sm", THALLIUM_SERVER_MODE);
    // Initialize the Sonata provider
    isonata::Provider provider = isonata::Provider::create(engine, backend);

    // Create an admin
    isonata::Admin admin = isonata::Admin::create(engine, backend);
    std::string addr = engine.self();

    // Create a database
    admin.createDatabase(addr, 0, "mydb", resource_type, resource_config);

    SECTION("Create client") {

      isonata::Client client = isonata::Client::create(engine, backend);

      SECTION("Open database") {

        auto db = client.open(addr, 0, "mydb");

        std::vector<std::string> docs = {
            "{\"name\":\"Matthieu\"}",
            "{\"name\":\"Rob\"}",
            "{\"name\":\"Phil\"}"
        };

        SECTION("Access collection") {
            auto coll = db.create("mycollection");

            REQUIRE_NOTHROW(coll.store("{\"name\":\"Matthieu\"}"));
            REQUIRE_NOTHROW(coll.store("{\"name\":\"Rob\"}"));
            REQUIRE_NOTHROW(coll.store("{\"name\":\"Phil\"}"));

            REQUIRE(coll.size() == 3);
            REQUIRE(coll.last_record_id() == 2);

            json record;
            REQUIRE_NOTHROW(coll.fetch(1, &record));

            REQUIRE(record.contains("name"));
            REQUIRE(record["name"] == "Rob");

            db.drop("mycollection");
        }

        SECTION("Access collection without blocking") {
            auto coll = db.create("mycollection");

            isonata::AsyncRequest store_reqs[3];
            uint64_t record_ids[3];
            REQUIRE_NOTHROW(coll.store(docs[0].data(), &record_ids[0], true, &store_reqs[0]));
            REQUIRE_NOTHROW(coll.store(docs[1].data(), &record_ids[1], true, &store_reqs[1]));
            REQUIRE_NOTHROW(coll.store(docs[2].data(), &record_ids[2], true, &store_reqs[2]));

            REQUIRE_NOTHROW(store_reqs[0].wait());
            REQUIRE_NOTHROW(store_reqs[1].wait());
            REQUIRE_NOTHROW(store_reqs[2].wait());

            REQUIRE(coll.size() == 3);
            REQUIRE(coll.last_record_id() == 2);

            json record;
            isonata::AsyncRequest fetch_req;
            REQUIRE_NOTHROW(coll.fetch(1, &record, &fetch_req));
            REQUIRE_NOTHROW(fetch_req.wait());

            REQUIRE(record.contains("name"));
            REQUIRE(record["name"] == "Rob");

            db.drop("mycollection");
        }

      }

    }

    // Destroy the database
    admin.destroyDatabase(addr, 0, "mydb");

    // Finalize the engine
    engine.finalize();
}
