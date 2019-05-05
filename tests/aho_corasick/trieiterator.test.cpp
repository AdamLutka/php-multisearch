#include "catch.hpp"

#include <string>
#include "trie.hpp"


using multisearch::ahocorasick::Trie;


TEST_CASE( "Trie iterator", "[Trie::iterator]" ) {


	SECTION("no empty key") {

		Trie<std::wstring, std::string> trie;
		trie.insert(L"arab", "arab data");
		trie.insert(L"ara", "ara data");
		trie.insert(L"baraba", "baraba data");
		trie.insert(L"bar", "bar data");
		trie.insert(L"barbar", "barbar data");
		trie.insert(L"brambor", "brambor data");

		SECTION("manual iteration") {
			auto it = trie.begin();

			REQUIRE(it->getKey() == L"ara");
			REQUIRE(it->getValue() == "ara data");
			++it;

			REQUIRE(it->getKey() == L"arab");
			REQUIRE(it->getValue() == "arab data");
			++it;

			REQUIRE(it->getKey() == L"bar");
			REQUIRE(it->getValue() == "bar data");
			++it;

			REQUIRE(it != trie.end());

			REQUIRE(it->getKey() == L"baraba");
			REQUIRE(it->getValue() == "baraba data");
			++it;

			REQUIRE(it->getKey() == L"barbar");
			REQUIRE(it->getValue() == "barbar data");
			++it;

			REQUIRE(it->getKey() == L"brambor");
			REQUIRE(it->getValue() == "brambor data");
			++it;

			REQUIRE(it == trie.end());
		}

		SECTION("foreach") {
			std::wstring keys[] = {L"ara", L"arab", L"bar", L"baraba", L"barbar", L"brambor"};
			int index = 0;

			for (auto& it : trie) {
				REQUIRE(it.getKey() == keys[index++]);
			}
		}
	}

	SECTION("empty key") {

		Trie<std::wstring, std::string> trie;
		trie.insert(L"ara", "ara data");
		trie.insert(L"", "{empty} data");

		auto it = trie.begin();

		REQUIRE(it->getKey() == L"");
		REQUIRE(it->getValue() == "{empty} data");
		++it;

		REQUIRE(it->getKey() == L"ara");
		REQUIRE(it->getValue() == "ara data");
		++it;

		REQUIRE(it == trie.end());
	}

	SECTION("national characters") {

		Trie<std::string, std::string> trie;
		trie.insert("dá", "");
		trie.insert("hled", "");
		trie.insert("hledá", "");
		trie.insert("led", "");

		auto it = trie.begin();

		REQUIRE(it->getKey() == "dá");
		++it;
		REQUIRE(it->getKey() == "hled");
		++it;
		REQUIRE(it->getKey() == "hledá");
		++it;
		REQUIRE(it->getKey() == "led");
		++it;

		REQUIRE(it == trie.end());
	}

}
