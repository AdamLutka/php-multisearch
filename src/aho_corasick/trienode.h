#ifndef MULTISEARCH_TRIENODE_H
#define MULTISEARCH_TRIENODE_H

#include <map>
#include <memory>

#include "trieautomatondata.h"
#include "trienodeiterator.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class TrieNode
		{
		private:
			using SelfT = TrieNode<KeyT, ValueT>;
			using AutomatonDataT = TrieAutomatonData<SelfT>;
			using ChildrenT = std::map<typename KeyT::value_type, std::unique_ptr<SelfT>>;

		public:
			using iterator = TrieNodeIterator<SelfT, typename ChildrenT::const_iterator>;
			using KeyStepT = typename KeyT::value_type;


			TrieNode() {}
			TrieNode(const SelfT& node)
			{
				*this = node;
			}
			TrieNode(SelfT&& node) = default;


			SelfT& operator=(const SelfT& node)
			{
				userData_ = node.userData_;
				automatonData_ = node.automatonData_;

				// deep copy of children
				children_.clear();
				for (auto& child : node.children_)
				{
					children_[child.first].reset(new SelfT(*child.second));
				}
				
				return *this;
			}

			SelfT& operator=(SelfT&& node) = default;


			ValueT& getUserData()
			{
				return userData_;
			}

			const ValueT& getUserData() const
			{
				return userData_;
			}


			AutomatonDataT& getAutomatonData()
			{
				return automatonData_;
			}

			const AutomatonDataT& getAutomatonData() const
			{
				return automatonData_;
			}


			SelfT& insertChild(const typename KeyT::value_type &key)
			{
				auto& child = children_[key];
				if (!child)
				{
					child.reset(new SelfT());
				}

				return *child;
			}

			iterator findChild(const typename KeyT::value_type &key) const
			{
				return iterator(children_.find(key));
			}


			iterator begin()
			{
				return iterator(children_.begin());
			}

			iterator end()
			{
				return iterator(children_.end());
			}


		private:
			ChildrenT children_;
			ValueT userData_;
			AutomatonDataT automatonData_;
		};

	}
}

#endif