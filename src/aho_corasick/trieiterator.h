#ifndef MULTISEARCH_TRIEITERATOR_H
#define MULTISEARCH_TRIEITERATOR_H

#include <vector>
#include <functional>
#include <utility>

#include "trienode.h"
#include "trierecord.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class TrieIterator
		{
		private:
			using SelfT = TrieIterator<KeyT, ValueT>;
			using NodeT = TrieNode<KeyT, ValueT>;

		public: 
			using iterator_category = std::forward_iterator_tag;
			using value_type = TrieRecord<KeyT, ValueT>;
			using difference_type = void;
			using pointer = value_type*;
			using reference = value_type&;


			TrieIterator() {}
			explicit TrieIterator(NodeT* node) : value_(KeyT(), node->getUserData())
			{
				trace_.push_back(TraceNode{ node->begin(), node->end() });
				if (!node->getAutomatonData().isTerminal()) {
					findTerminal();
				}
			}


			SelfT& operator ++()
			{
				findTerminal();
				
				return *this;
			}

			const value_type& operator *() const
			{
				return value_;
			}

			const value_type* operator ->() const
			{
				return std::addressof(value_);
			}

			bool operator ==(const SelfT& it) const
			{
				return it.trace_.size() == trace_.size() && (trace_.empty() || it.trace_.back().iterator == trace_.back().iterator);
			}

			bool operator !=(const SelfT& it) const
			{
				return !(*this == it);
			}

		private:
			struct TraceNode
			{
				typename NodeT::iterator iterator, endIterator;
			};


			KeyT createKey() const
			{
				KeyT key;
				for (auto& it : trace_) {
					key.push_back(it.iterator->getKeyStep());
				}

				return key;
			}

			bool findTerminal()
			{
				while (!trace_.empty())
				{
					if (trace_.back().iterator == trace_.back().endIterator)
					{
						trace_.pop_back();
						if (!trace_.empty())
						{
							++trace_.back().iterator;
						}

						continue;
					}

					auto& node = trace_.back().iterator->getChild();
					bool isTerminal = node.getAutomatonData().isTerminal();
					
					if (isTerminal)
					{
						value_ = value_type(createKey(), node.getUserData());
					}

					trace_.push_back(TraceNode{ node.begin(), node.end() });

					if (isTerminal)
					{
						return true;
					}
				}

				value_ = value_type();
				return false;
			}


			value_type value_;
			std::vector<TraceNode> trace_;
		};

	}
}

#endif