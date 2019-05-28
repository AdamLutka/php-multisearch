#include "catch.hpp"

#include <string>
#include "trie.hpp"


using multisearch::ahocorasick::Trie;


TEST_CASE( "Trie remove", "[Trie.remove]" ) {

	Trie<std::wstring, std::string> trie;
	trie.insert(L"", "");
	trie.insert(L"key1", "value1");
	trie.insert(L"key2", "value2");
	trie.insert(L"key3", "value3");

	SECTION("remove existing key") {
		REQUIRE(trie.remove(L"key2") == true);
		REQUIRE(trie.find(L"key2") == trie.end());
	}

	SECTION("remove empty key") {
		REQUIRE(trie.remove(L"") == true);
		REQUIRE(trie.find(L"") == trie.end());
	}

	SECTION("remove substring") {
		REQUIRE(trie.remove(L"key") == false);
		REQUIRE(trie.find(L"key") == trie.end());
		REQUIRE(trie.find(L"key1") != trie.end());
		REQUIRE(trie.find(L"key2") != trie.end());
		REQUIRE(trie.find(L"key3") != trie.end());
	}

	SECTION("remove not existing key") {
		REQUIRE(trie.remove(L"wrong") == false);
		REQUIRE(trie.find(L"wrong") == trie.end());
	}

}
