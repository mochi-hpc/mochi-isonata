/*
 * (C) 2023 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <isonata/Admin.hpp>
#include <isonata/Provider.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/catch_all.hpp>

using namespace Catch::Generators;

static const std::string resource_type = "unqlite";
static constexpr const char* resource_config = "{ \"path\" : \"mydb\", \"mode\":\"create\" }";

TEST_CASE("Admin tests", "[admin]") {

    auto backend = GENERATE(as<std::string>{}, "yokan", "sonata");

    auto engine = thallium::engine("na+sm", THALLIUM_SERVER_MODE);
    // Initialize the Sonata provider
    isonata::Provider provider = isonata::Provider::create(engine, backend);

    SECTION("Create an admin") {
        isonata::Admin admin = isonata::Admin::create(engine, backend);
        std::string addr = engine.self();

        SECTION("Create and destroy databases") {
            REQUIRE_NOTHROW(admin.createDatabase(addr, 0, "mydb", resource_type, resource_config));
            REQUIRE_NOTHROW(admin.destroyDatabase(addr, 0, "mydb"));
            REQUIRE_THROWS_AS(admin.createDatabase(addr, 0, "mydb", "blabla", resource_config),
                              isonata::Exception);
            REQUIRE_THROWS_AS(admin.destroyDatabase(addr, 0, "unknown"), isonata::Exception);
        }
    }
    // Finalize the engine
    engine.finalize();
}
