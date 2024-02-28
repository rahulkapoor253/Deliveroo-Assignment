#define CATCH_CONFIG_MAIN
#include "../external/catch.hpp"

#include "../program/main.cpp"

TEST_CASE("TEST CRON PARSER - MINUTE") {
    CronParser cp("*/15 0 1,15 * 1-5", "/usr/bin/find");

    int arr[] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    vector<int> mins(arr, arr + 60);

    REQUIRE(mins == cp.getMinutes());
};

TEST_CASE("TEST CRON PARSER - HOUR") {
    CronParser cp("*/15 0 1,15 * 1-5", "/usr/bin/find");

    int arr[] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    vector<int> hours(arr, arr + 24);

    REQUIRE(hours == cp.getHours());
};

TEST_CASE("TEST CRON PARSER - day of month") {
    CronParser cp("*/15 0 1,15 * 1-5", "/usr/bin/find");

    int arr[] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    vector<int> dom(arr, arr + 32);

    REQUIRE(dom == cp.getDayOfMonth());
};

TEST_CASE("TEST CRON PARSER - MONTH") {
    CronParser cp("*/15 0 1,15 * 1-5", "/usr/bin/find");

    int arr[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    vector<int> month(arr, arr + 13);

    REQUIRE(month == cp.getMonth());
};

TEST_CASE("TEST CRON PARSER - day of week") {
    CronParser cp("*/15 0 1,15 * 1-5", "/usr/bin/find");

    int arr[] = { 0, 1, 1, 1, 1, 1, 0 };
    vector<int> dow(arr, arr + 7);

    REQUIRE(dow == cp.getDayOfWeek());
};