#ifndef MULTISEARCH_AHOC_TRIE_HPP
#define MULTISEARCH_AHOC_TRIE_HPP

#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <stdexcept>

#define NULL_NODE_INDEX UINT32_MAX
#define ROOT_NODE_INDEX 0

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class Trie
		{
		public:
			using TrieT = Trie<KeyT, ValueT>;
			using KeyPartT = typename KeyT::value_type;

		private:
			using NodeIndexT = std::uint32_t;


			struct TrieNode
			{
				using ChildrenT = std::vector<NodeIndexT>;

				NodeIndexT parent = NULL_NODE_INDEX;
				NodeIndexT fail = NULL_NODE_INDEX;
				NodeIndexT output = NULL_NODE_INDEX;
				bool is_terminal = false;
				ChildrenT children;
				KeyPartT key_part;
				ValueT value;

				explicit TrieNode(const KeyPartT& kp) : key_part(kp) {}
			};


			typename TrieNode::ChildrenT::const_iterator find_child(const TrieNode& node, const KeyPartT& key_part) const
			{
				for (auto it = node.children.cbegin(); it != node.children.cend(); ++it)
				{
					if (nodes_[*it].key_part == key_part)
					{
						return it;
					}
				}

				return node.children.cend();
			}

			void insert_child(TrieNode& node, NodeIndexT child)
			{
				node.children.push_back(child);
			}

			void sort_children()
			{
				for (auto& node : nodes_)
				{
					std::sort(node.children.begin(), node.children.end(), [this](const NodeIndexT & a, const NodeIndexT & b) {
						return this->nodes_[a].key_part < this->nodes_[b].key_part;
					});
				}
			}

			void build_automaton()
			{
				std::queue<NodeIndexT> queue;
				auto& root = nodes_[ROOT_NODE_INDEX];

				for (auto child_index : root.children)
				{
					auto& child = nodes_[child_index];
					child.fail = ROOT_NODE_INDEX;
					child.output = root.is_terminal ? ROOT_NODE_INDEX : NULL_NODE_INDEX;

					for (auto child_child_index : child.children)
					{
						queue.push(child_child_index);
					}
				}

				while (!queue.empty())
				{
					auto current_index = queue.front();
					auto& current = nodes_[current_index];
					queue.pop();

					for (auto child_index : current.children)
					{
						queue.push(child_index);
					}

					// fail
					auto fail = nodes_[current.parent].fail;
					while (fail != NULL_NODE_INDEX)
					{
						auto& fail_node = nodes_[fail];
						auto it = find_child(fail_node, current.key_part);

						if (it != fail_node.children.end())
						{
							current.fail = *it;
							break;
						}
						else if (fail == ROOT_NODE_INDEX)
						{
							current.fail = ROOT_NODE_INDEX;
							break;
						}

						fail = fail_node.fail;
					}

					// output
					fail = current.fail;
					while (fail != NULL_NODE_INDEX)
					{
						auto& fail_node = nodes_[fail];
						if (fail_node.is_terminal)
						{
							current.output = fail;
							break;
						}

						fail = fail_node.fail;
					}
				}
			}


			std::vector<TrieNode> nodes_;
			bool need_build_ = false;
			bool need_sort_ = false;

		public:

			class iterator
			{
			public:
				class value_type
				{
				public:
					friend iterator;

					value_type(const KeyT& k) : key(k) {}

					const KeyT& getKey() const { return key; }
					ValueT& getValue() const { return *value; }

				private:
					KeyT key;
					ValueT* value = nullptr;
				};

				using iterator_category = std::forward_iterator_tag;
				using difference_type = void;
				using pointer = value_type*;
				using reference = value_type&;


				iterator(TrieT& trie, const NodeIndexT& node_index, const KeyT& key) : trie_(trie), current_node_(node_index), value_(key)
				{
					if (node_index != NULL_NODE_INDEX && !trie_.nodes_[current_node_].is_terminal)
					{
						this->operator++();
					}
				}


				iterator& operator ++()
				{
					if (current_node_ != NULL_NODE_INDEX)
					{
						value_.value = nullptr;
						while (current_node_ != NULL_NODE_INDEX)
						{
							typename TrieNode::ChildrenT::const_iterator it;
							while ((it = trie_.nodes_[current_node_].children.cbegin()) != trie_.nodes_[current_node_].children.cend())
							{
								current_node_ = *it;
								value_.key.push_back(trie_.nodes_[current_node_].key_part);
								if (trie_.nodes_[current_node_].is_terminal)
								{
									return *this;
								}
							}

							while (trie_.nodes_[current_node_].parent != NULL_NODE_INDEX)
							{
								auto& pnode = trie_.nodes_[current_node_];
								auto& parent = trie_.nodes_[pnode.parent];
								auto it = trie_.find_child(parent, pnode.key_part);

								current_node_ = pnode.parent;
								value_.key.pop_back();

								if (++it == parent.children.end())
								{
									continue;
								}

								current_node_ = *it;
								auto& nnode = trie_.nodes_[current_node_];
								value_.key.push_back(nnode.key_part);

								if (nnode.is_terminal)
								{
									return *this;
								}
								else
								{
									break;
								}
							}

							if (trie_.nodes_[current_node_].parent == NULL_NODE_INDEX)
							{
								current_node_ = NULL_NODE_INDEX;
							}
						}
					}

					return *this;
				}

				const reference operator *()
				{
					if (current_node_ != NULL_NODE_INDEX && value_.value == nullptr)
					{
						value_.value = &trie_.nodes_[current_node_].value;
					}

					return value_;
				}

				const pointer operator ->()
				{
					return std::addressof(this->operator*());
				}

				bool operator ==(const iterator& it) const
				{
					return &trie_ == &it.trie_ && current_node_ == it.current_node_;
				}

				bool operator !=(const iterator& it) const
				{
					return !(*this == it);
				}

			private:
				TrieT& trie_;
				NodeIndexT current_node_;
				value_type value_;
			};


			class search_iterator
			{
			public:
				class value_type
				{
				public:
					friend search_iterator;

					const KeyT& getKey() const { return key; }
					ValueT& getValue() const { return *value; }
					std::size_t getPosition() { return position; }

				private:
					KeyT key;
					ValueT* value = nullptr;
					std::size_t position = 0;
				};

				using pointer = value_type *;
				using reference = value_type &;


				search_iterator(TrieT& trie, const KeyT& haystack) : trie_(trie), haystack_(haystack), haystack_it_(haystack_.cbegin()) {}


				bool operator ++()
				{
					value_.value = nullptr;

					if (output_ != NULL_NODE_INDEX && trie_.nodes_[output_].output != NULL_NODE_INDEX)
					{
						output_ = trie_.nodes_[output_].output;
						return true;
					}

					while (haystack_it_ != haystack_.cend())
					{
						do
						{
							auto& node = trie_.nodes_[node_];
							auto it = trie_.find_child(node, *haystack_it_);

							if (it != node.children.end())
							{	// we found next step
								node_ = *it;
								break;
							}
							else if (node.fail != NULL_NODE_INDEX)
							{	// we go back using failure link
								node_ = node.fail;
							}
							else
							{	// we are in the root and there is no next step
								break;
							}

						} while (true);

						++haystack_it_;

						if (trie_.nodes_[node_].is_terminal)
						{
							output_ = node_;
							return true;
						}
					}

					return false;
				}

				const reference operator *()
				{
					if (value_.value == nullptr)
					{
						value_.key.clear();
						auto curr = output_;
						while (trie_.nodes_[curr].parent != NULL_NODE_INDEX)
						{
							value_.key.push_back(trie_.nodes_[curr].key_part);
							curr = trie_.nodes_[curr].parent;
						}	
						std::reverse(value_.key.begin(), value_.key.end());

						value_.value = &trie_.nodes_[output_].value;
						value_.position = (haystack_it_ - haystack_.cbegin()) - value_.key.size();
					}

					return value_;
				}

				const pointer operator ->()
				{
					return std::addressof(this->operator*());
				}

			private:
				TrieT& trie_;
				const KeyT haystack_;
				typename KeyT::const_iterator haystack_it_;
				NodeIndexT node_ = ROOT_NODE_INDEX;
				NodeIndexT output_ = NULL_NODE_INDEX;
				value_type value_;
			};


			Trie()
			{
				nodes_.emplace_back(0);
			}


			void insert(const KeyT& key, const ValueT& value)
			{
				NodeIndexT current = ROOT_NODE_INDEX;

				for (auto& key_part : key)
				{
					auto it = find_child(nodes_[current], key_part);
					NodeIndexT child_index;

					if (it == nodes_[current].children.end())
					{
						child_index = nodes_.size();
						if (child_index == NULL_NODE_INDEX)
						{
							throw std::runtime_error("There is no space left inside the trie.");
						}

						nodes_.emplace_back(key_part);
						nodes_[child_index].parent = current;
						insert_child(nodes_[current], child_index);
					}
					else
					{
						child_index = *it;
					}

					current = child_index;
				}

				nodes_[current].value = value;
				nodes_[current].is_terminal = true;

				need_build_ = true;
				need_sort_ = true;
			}

			search_iterator search_in(const KeyT& haystack)
			{
				if (need_build_)
				{
					build_automaton();
					need_build_ = false;
				}

				return search_iterator(*this, haystack);
			}


			std::size_t get_byte_size() const
			{
				std::size_t size = 0;

				for (auto& node : nodes_)
				{
					size += sizeof(TrieNode) + sizeof(typename TrieNode::ChildrenT::value_type) * node.children.size();
				}

				return size;
			}

			std::size_t get_nodes_count() const
			{
				return nodes_.size();
			}


			iterator begin()
			{
				if (need_sort_)
				{
					sort_children();
					need_sort_ = false;
				}

				return iterator(*this, ROOT_NODE_INDEX, KeyT());
			}

			iterator end()
			{
				return iterator(*this, NULL_NODE_INDEX, KeyT());
			}

			iterator find(const KeyT& key)
			{
				NodeIndexT current = ROOT_NODE_INDEX;

				for (auto& key_part : key)
				{
					auto it = find_child(nodes_[current], key_part);
					if (it == nodes_[current].children.end())
					{
						return end();
					}

					current = *it;
				}

				if (nodes_[current].is_terminal)
				{
					return iterator(*this, current, key);
				}
				else
				{
					return end();
				}
			}
		};

	}
}

#endif