#ifndef MULTISEARCH_AHOC_TRIEAUTOMATONDATA_H
#define MULTISEARCH_AHOC_TRIEAUTOMATONDATA_H

#include <cstddef>

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename NodeT>
		class TrieAutomatonData
		{
		private:
			using SelfT = TrieAutomatonData<NodeT>;
		public:
			
			TrieAutomatonData() {}
			TrieAutomatonData(const SelfT& data) : depth_(data.depth_), isTerminal_(data.isTerminal_) {}


			std::size_t getDepth() const
			{
				return depth_;
			}

			void setDepth(std::size_t depth)
			{
				depth_ = depth;
			}


			bool isTerminal() const
			{
				return isTerminal_;
			}

			void setIsTerminal(bool isTerminal)
			{
				isTerminal_ = isTerminal;
			}


			bool hasFailureLink() const
			{
				return nullptr != failureLink_;
			}

			NodeT* const getFailureLink() const
			{
				return failureLink_;
			}

			void setFailureLink(NodeT* const node)
			{
				failureLink_ = node;
			}


			bool hasOutputLink() const
			{
				return nullptr != outputLink_;
			}

			NodeT* const getOutputLink() const
			{
				return outputLink_;
			}

			void setOutputLink(NodeT* const node)
			{
				outputLink_ = node;
			}


		private:
			NodeT* failureLink_ = nullptr;
			NodeT* outputLink_ = nullptr;
			std::size_t depth_ = 0;
			bool isTerminal_ = false;
		};

	}
}

#endif