#ifndef MULTISEARCH_TRIEAUTOMATONPREPARER_H
#define MULTISEARCH_TRIEAUTOMATONPREPARER_H

#include <functional>
#include <queue>

#include "trienode.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class TrieAutomatonPreparer
		{
		private:
			using NodeT = TrieNode<KeyT, ValueT>;

		public:
			explicit TrieAutomatonPreparer(NodeT& root) : root_(root) {}


			void build()
			{
				processRootChildren();
				createFailureLinks();
				createOutputLinks();
			}


		private:
			struct QueueItem
			{
				NodeT* parent;
				typename KeyT::value_type edgeValue;
				NodeT* child;

				QueueItem(NodeT* p, typename KeyT::value_type ev, NodeT* ch)
					: parent(p), edgeValue(ev), child(ch) {}
			};


			void bfs(std::function<void(QueueItem)> itemCallback)
			{
				std::queue<QueueItem> queue;

				// init queue
				//  - root children are skipped, have to be processed separately
				for (auto& rootIt : root_)
				{
					for (auto& rootChildIt : rootIt.getChild())
					{
						queue.emplace(&rootIt.getChild(), rootChildIt.getKeyStep(), &rootChildIt.getChild());
					}
				}

				// proccess queue
				while (!queue.empty())
				{
					auto queueItem = queue.front();
					queue.pop();

					for (auto& it : *queueItem.child)
					{
						queue.emplace(queueItem.child, it.getKeyStep(), &it.getChild());
					}

					itemCallback(queueItem);
				}
			}


			void processRootChildren()
			{
				bool isRootTerminal = root_.getAutomatonData().isTerminal();

				for (auto& rootIt : root_)
				{
					auto& data = rootIt.getChild().getAutomatonData();
					data.setFailureLink(&root_);
					data.setDepth(1);
					if (isRootTerminal) {
						data.setOutputLink(&root_);
					}
				}
			}

			void createFailureLinks()
			{
				bfs([this](QueueItem queueItem) {

					auto& parentData = queueItem.parent->getAutomatonData();
					auto& childData = queueItem.child->getAutomatonData();

					childData.setDepth(parentData.getDepth() + 1);

					auto failureNode = parentData.getFailureLink();
					while (failureNode != nullptr)
					{
						auto it = failureNode->findChild(queueItem.edgeValue);

						if (it != failureNode->end())
						{
							childData.setFailureLink(&it->getChild());
							break;
						}
						else if (failureNode == &root_)
						{
							childData.setFailureLink(&root_);
							break;
						}

						failureNode = failureNode->getAutomatonData().getFailureLink();
					}

				});
			}

			void createOutputLinks()
			{
				bfs([](QueueItem queueItem) {

					auto node = queueItem.child;
					auto fail = node->getAutomatonData().getFailureLink();

					while (fail != nullptr)
					{
						if (fail->getAutomatonData().isTerminal())
						{
							node->getAutomatonData().setOutputLink(fail);
							break;
						}

						fail = fail->getAutomatonData().getFailureLink();
					}

				});
			}

			
			NodeT& root_;
		};

	}
}

#endif