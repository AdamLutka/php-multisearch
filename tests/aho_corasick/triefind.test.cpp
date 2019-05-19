#include "catch.hpp"

#include <string>
#include "trie.hpp"


using multisearch::ahocorasick::Trie;


TEST_CASE( "Trie find", "[Trie.find]" ) {

	Trie<std::wstring, std::string> trie;
	trie.insert(L"", "");
	trie.insert(L"key1", "value1");
	trie.insert(L"key2", "value2");
	trie.insert(L"key3", "value3");

	SECTION("found middle") {
		auto it = trie.find(L"key2");

		REQUIRE(it->getKey() == L"key2");
		REQUIRE(it->getValue() == "value2");

		++it;

		REQUIRE(it->getKey() == L"key3");
		REQUIRE(it->getValue() == "value3");

		++it;

		REQUIRE(it == trie.end());
	}

	SECTION("found last") {
		auto it = trie.find(L"key3");

		REQUIRE(it->getKey() == L"key3");
		REQUIRE(it->getValue() == "value3");

		++it;

		REQUIRE(it == trie.end());
	}

	SECTION("found empty") {
		auto it = trie.find(L"");

		REQUIRE(it->getKey() == L"");
		REQUIRE(it->getValue() == "");
	}

	SECTION("not found") {
		auto it = trie.find(L"nokey");

		REQUIRE(it == trie.end());
	}

}
