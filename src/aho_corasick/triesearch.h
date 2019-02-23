#ifndef MULTISEARCH_TRIESEARCH_H
#define MULTISEARCH_TRIESEARCH_H

#include <memory>
#include <iterator>

#include "triehit.h"
#include "trienode.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class TrieSearch
		{
		private:
			using NodeT = TrieNode<KeyT, ValueT>;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = TrieHit<KeyT, ValueT>;
			using difference_type = void;
			using pointer = value_type*;
			using reference = value_type&;


			TrieSearch(const KeyT& haystack, NodeT& node) : haystack_(haystack), root_(&node), node_(&node), haystackIt_(haystack_.cbegin()) {}


			bool operator++()
			{
				if (nullptr != outputLink_)
				{
					hit(outputLink_);
					return true;
				}
				
				while (haystackIt_ != haystack_.cend())
				{
					do
					{
						auto it = node_->findChild(*haystackIt_);

						if (it != node_->end())
						{	// we found next step
							node_ = &it->getChild();
							break;
						}
						else if (node_->getAutomatonData().hasFailureLink())
						{	// we go back using failure link
							node_ = node_->getAutomatonData().getFailureLink();
						}
						else
						{	// we are in the root and there is no next step
							break;
						}

					} while (true);

					++haystackIt_;

					if (node_->getAutomatonData().isTerminal())
					{
						hit(node_);
						return true;
					}
				}

				return false;
			}

			reference operator*()
			{
				return hit_;
			}

			pointer operator->()
			{
				return std::addressof(hit_);
			}

		private:
			void hit(NodeT* node)
			{
				KeyT key;
				auto& automatonData = node->getAutomatonData();
				auto depth = automatonData.getDepth();

				std::copy(haystackIt_ - depth, haystackIt_, std::back_inserter(key));
				hit_ = value_type(key, node->getUserData(), haystackIt_ - haystack_.cbegin() - depth);
				outputLink_ = automatonData.getOutputLink();
			}


			const KeyT haystack_;
			NodeT* root_;
			NodeT* node_;
			typename KeyT::const_iterator haystackIt_;
			value_type hit_;
			NodeT* outputLink_ = nullptr;
			
		};

	}
}

#endif