#include "catch.hpp"

#include <string>
#include "trie.h"


using multisearch::ahocorasick::Trie;


TEST_CASE( "Trie", "[Trie]" ) {

	std::wstring haystack = L"key1 key2";

	Trie<std::wstring, std::string> trie1;
	trie1.insert(L"key1", "value1");

	SECTION("copy") {
		Trie<std::wstring, std::string> trie2(trie1);
		trie2.insert(L"key2", "value2");

		auto sIt1 = trie1.searchIn(haystack);
		auto sIt2 = trie2.searchIn(haystack);

		REQUIRE(++sIt1 == true);
		REQUIRE(sIt1->getKey() == L"key1");
		REQUIRE(++sIt1 == false);

		REQUIRE(++sIt2 == true);
		REQUIRE(sIt2->getKey() == L"key1");
		REQUIRE(++sIt2 == true);
		REQUIRE(sIt2->getKey() == L"key2");
		REQUIRE(++sIt2 == false);
	}

	SECTION("asign") {
		Trie<std::wstring, std::string> trie2;
		trie2 = trie1;
		trie2.insert(L"key2", "value2");

		auto sIt1 = trie1.searchIn(haystack);
		auto sIt2 = trie2.searchIn(haystack);

		REQUIRE(++sIt1 == true);
		REQUIRE(sIt1->getKey() == L"key1");
		REQUIRE(++sIt1 == false);

		REQUIRE(++sIt2 == true);
		REQUIRE(sIt2->getKey() == L"key1");
		REQUIRE(++sIt2 == true);
		REQUIRE(sIt2->getKey() == L"key2");
		REQUIRE(++sIt2 == false);
	}

	SECTION("move") {
		Trie<std::wstring, std::string> trie2(std::move(trie1));
		trie2.insert(L"key2", "value2");

		auto sIt1 = trie1.searchIn(haystack);
		auto sIt2 = trie2.searchIn(haystack);

		REQUIRE(++sIt1 == false);

		REQUIRE(++sIt2 == true);
		REQUIRE(sIt2->getKey() == L"key1");
		REQUIRE(++sIt2 == true);
		REQUIRE(sIt2->getKey() == L"key2");
		REQUIRE(++sIt2 == false);
	}

}
