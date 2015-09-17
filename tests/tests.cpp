#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/trivial.h"

TEST_CASE("is primitive a trivial class") {
	REQUIRE(std::is_trivial<primitives>::value == true);
}

TEST_CASE("primitive instance") {
	primitives p = {2, 3.7, {1,2}};
	REQUIRE(p.x == 2);
	REQUIRE(p.y == 3.7f);
	REQUIRE(p.a[0] == 1);
	REQUIRE(p.a[1] == 2);
}

TEST_CASE("is constructor a trivial class") {
	REQUIRE(std::is_trivial<constructor>::value == true);
}

TEST_CASE("assingment of a value to constructor struct") {
	constructor c1;
	c1.x = 5;
	REQUIRE(c1.x == 5);

	constructor c2 = { 4 };
	REQUIRE(c2.x == 4);

	constructor c3 { 6 };
	REQUIRE(c3.x == 6);
}

TEST_CASE("is with_static a trivial class") {
	REQUIRE(std::is_trivial<with_static>::value == true);
}

TEST_CASE("usage of with_static") {
	REQUIRE(with_static::f() == -1);
	with_static ws = {10};
	REQUIRE(ws.x == 10);
}

TEST_CASE("not_trivial_1 should not be a trivial class") {
	REQUIRE(std::is_trivial<not_trivial_1>::value == false);
}

TEST_CASE("is primitives class a standard layout") {
	REQUIRE(std::is_standard_layout<primitives>::value == true);
}

TEST_CASE("is constructor class a standard layout") {
	REQUIRE(std::is_standard_layout<constructor>::value == true);
}

TEST_CASE("is with_static class a standard layout") {
	REQUIRE(std::is_standard_layout<with_static>::value == true);
}

TEST_CASE("are they pods?") {
	REQUIRE(std::is_pod<primitives>::value == true);
	REQUIRE(std::is_pod<constructor>::value == true);
	REQUIRE(std::is_pod<with_static>::value == true);
}

TEST_CASE("Copy of primitives with memcpy are the same") {
	primitives p1 = { 2, 3.7f, {9, 10} };
	primitives p2;
	std::memcpy(&p1, &p2, sizeof(primitives));

	REQUIRE(p1.x == p2.x);
	REQUIRE(p1.y == p2.y);
	REQUIRE(p1.a[0] == p2.a[0]);
	REQUIRE(p1.a[1] == p2.a[1]);
}

TEST_CASE("test with memset") {
	primitives p1 = { 1, 2.0, {3, 4} };
	std::memset(&p1, 0, sizeof(primitives));

	REQUIRE(p1.x == 0);
	REQUIRE(p1.y == 0);
	REQUIRE(p1.a[0] == 0);
	REQUIRE(p1.a[1] == 0);
}

TEST_CASE("test with memcmp") {
	primitives p1 = { 1, 2.0, {3, 4} };
	primitives p2 = { 2, 3.7f, {9, 10} };
	primitives p3 = { 1, 2.0, {3, 4} };

	REQUIRE(std::memcmp(&p1, &p2, sizeof(primitives)) != 0);
	REQUIRE(std::memcmp(&p1, &p3, sizeof(primitives)) == 0);
}

TEST_CASE("test between pod and non pod with memcmp") {
	primitives p1 = { 1, 2.0, {3, 4} };
	not_trivial_2 p2;
	p2.x = 1;
	p2.y = 2.0f;
	p2.a[0] = 3;
	p2.a[1] = 4;

	REQUIRE(std::memcmp(&p1, &p2, sizeof(primitives)) != 0);
}
