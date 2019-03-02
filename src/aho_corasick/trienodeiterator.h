#ifndef MULTISEARCH_AHOC_TRIENODEITERATOR_H
#define MULTISEARCH_AHOC_TRIENODEITERATOR_H

#include <memory>

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename NodeT, typename IteratorT>
		class TrieNodeIterator
		{
		private:
			using SelfT = TrieNodeIterator<NodeT, IteratorT>;
			
		public:
			class value_type
			{
			public:
				friend class TrieNodeIterator<NodeT, IteratorT>;

				
				value_type() {}
				explicit value_type(const IteratorT& iterator) : iterator_(iterator) {}


				typename NodeT::KeyStepT getKeyStep() const
				{
					return iterator_->first;
				}

				NodeT& getChild() const
				{
					return *(iterator_->second);
				}

			private:
				IteratorT iterator_;
			};


			using iterator_category = std::forward_iterator_tag;
			using difference_type = void;
			using pointer = value_type * ;
			using reference = value_type & ;


			TrieNodeIterator() {}
			explicit TrieNodeIterator(const IteratorT& iterator) : value_(iterator) {}


			SelfT& operator ++()
			{
				++(value_.iterator_);
				
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
				return value_.iterator_ == it.value_.iterator_;
			}

			bool operator !=(const SelfT& it) const
			{
				return !(*this == it);
			}


		private:
			value_type value_;

		};

	}
}

#endif