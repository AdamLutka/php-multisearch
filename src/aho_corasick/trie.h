#ifndef MULTISEARCH_TRIE_H
#define MULTISEARCH_TRIE_H

#include "trienode.h"
#include "trieiterator.h"
#include "triesearch.h"
#include "trieautomatonpreparer.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class Trie
		{
		private:
			using SelfT = Trie<KeyT, ValueT>;
			using NodeT = TrieNode<KeyT, ValueT>;

		public:
			using iterator = TrieIterator<KeyT, ValueT>;


			Trie() {}
			Trie(const SelfT& trie)
			{
				*this = trie;
			}
			Trie(SelfT&& trie)
			{
				*this = std::move(trie);
			}


			SelfT& operator=(const SelfT& trie)
			{
				root_ = trie.root_;
				needBuild_ = true;

				return *this;
			}

			SelfT& operator=(SelfT&& trie)
			{
				root_ = std::move(trie.root_);
				needBuild_ = trie.needBuild_;
				trie.root_ = NodeT();

				return *this;
			}


			void insert(const KeyT& key, const ValueT& value)
			{
				auto current = &root_;

				for (auto& keyStep : key)
				{
					current = &current->insertChild(keyStep);
				}

				current->getUserData() = value;
				current->getAutomatonData().setIsTerminal(true);
				needBuild_ = true;
			}

			TrieSearch<KeyT, ValueT> searchIn(const KeyT& haystack)
			{
				if (needBuild_)
				{
					TrieAutomatonPreparer<KeyT, ValueT> automatonPreparer(root_);
					automatonPreparer.build();
					needBuild_ = false;
				}

				return TrieSearch<KeyT, ValueT>(haystack, root_);
			}


			iterator begin()
			{
				return iterator(&root_);
			}

			iterator end()
			{
				return iterator();
			}


		private:
			NodeT root_;
			bool needBuild_ = false;

		};

	}
}

#endif