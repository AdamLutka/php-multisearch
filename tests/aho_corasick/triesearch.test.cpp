#include "catch.hpp"

#include <string>
#include "trie.hpp"

using multisearch::ahocorasick::Trie;


TEST_CASE( "Trie search", "[Trie::search_iterator]" ) {

	SECTION("regular search") {

		Trie<std::wstring, std::string> trie;
		trie.insert(L"arab", "arab data");
		trie.insert(L"ara", "ara data");
		trie.insert(L"baraba", "baraba data");
		trie.insert(L"bar", "bar data");
		trie.insert(L"barbar", "barbar data");
		trie.insert(L"brambor", "brambor data");
		trie.insert(L"rab", "rab data");

		auto sIt = trie.search_in(L"barbarsky arab");

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

		auto sIt = trie.search_in(L"");

		REQUIRE(++sIt == false);

	}

	SECTION("search no needles") {

		Trie<std::wstring, std::string> trie;

		auto sIt = trie.search_in(L"lorem ipsum...");

		REQUIRE(++sIt == false);

	}

	SECTION("concatenated keys") {

		Trie<std::wstring, std::string> trie;
		trie.insert(L"key1", "value1");
		trie.insert(L"key2", "value2");

		auto sIt = trie.search_in(L"key1key2");

		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == L"key1");
		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == L"key2");
		REQUIRE(++sIt == false);

	}

	SECTION("national characters") {
		Trie<std::string, std::string> trie;
		trie.insert("dá", "");
		trie.insert("hled", "");
		trie.insert("hledá", "");
		trie.insert("led", "");

		auto sIt = trie.search_in("vyhledávací");

		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == "hled");
		REQUIRE(sIt->getPosition() == 2);

		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == "led");
		REQUIRE(sIt->getPosition() == 3);

		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == "hledá");
		REQUIRE(sIt->getPosition() == 2);

		REQUIRE(++sIt == true);
		REQUIRE(sIt->getKey() == "dá");
		REQUIRE(sIt->getPosition() == 5);

		REQUIRE(++sIt == false);
	}

}
