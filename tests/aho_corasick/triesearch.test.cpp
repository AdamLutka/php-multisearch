#include "catch.hpp"

#include <string>
#include "trie.h"


using multisearch::ahocorasick::Trie;


TEST_CASE( "Trie search", "[TrieSearch]" ) {


	SECTION("regular search") {

        Trie<std::wstring, std::string> trie;
        trie.insert(L"arab", "arab data");
        trie.insert(L"ara", "ara data");
        trie.insert(L"baraba", "baraba data");
        trie.insert(L"bar", "bar data");
        trie.insert(L"barbar", "barbar data");
    	trie.insert(L"brambor", "brambor data");
        trie.insert(L"rab", "rab data");

        auto sIt = trie.searchIn(L"barbarsky arab");

        REQUIRE(++sIt == true);
        REQUIRE(sIt->getKey() == L"bar");
        REQUIRE(sIt->getValue() == "bar data");
        REQUIRE(sIt->getPosition() == 0);

        REQUIRE(++sIt == true);
        REQUIRE(sIt->getKey() == L"barbar");
        REQUIRE(sIt->getValue() == "barbar data");
        REQUIRE(sIt->getPosition() == 0);

        REQUIRE(++sIt == true);
        REQUIRE(sIt->getKey() == L"bar");
        REQUIRE(sIt->getValue() == "bar data");
        REQUIRE(sIt->getPosition() == 3);

        REQUIRE(++sIt == true);
        REQUIRE(sIt->getKey() == L"ara");
        REQUIRE(sIt->getValue() == "ara data");
        REQUIRE(sIt->getPosition() == 10);

        REQUIRE(++sIt == true);
        REQUIRE(sIt->getKey() == L"arab");
        REQUIRE(sIt->getValue() == "arab data");
        REQUIRE(sIt->getPosition() == 10);

        REQUIRE(++sIt == true);
        REQUIRE(sIt->getKey() == L"rab");
        REQUIRE(sIt->getValue() == "rab data");
        REQUIRE(sIt->getPosition() == 11);

        REQUIRE(++sIt == false);
        REQUIRE(++sIt == false);

	}

    SECTION("search in empty haystack") {
        
        Trie<std::wstring, std::string> trie;
        trie.insert(L"abc", "data");

        auto sIt = trie.searchIn(L"");

        REQUIRE(++sIt == false);

    }

    SECTION("search no needles") {

        Trie<std::wstring, std::string> trie;

        auto sIt = trie.searchIn(L"lorem ipsum...");

        REQUIRE(++sIt == false);

    }

	SECTION("concatenated keys") {
		
		Trie<std::wstring, std::string> trie;
		trie.insert(L"key1", "value1");
		trie.insert(L"key2", "value2");

		auto sIt = trie.searchIn(L"key1key2");

		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == L"key1");
		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == L"key2");
		REQUIRE(++sIt == false);

	}

}
