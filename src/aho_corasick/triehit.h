#ifndef MULTISEARCH_AHOC_TRIEHIT_H
#define MULTISEARCH_AHOC_TRIEHIT_H

#include <cstddef>

#include "valuereference.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class TrieHit
		{
		public:
			TrieHit() : position_(0) {}
			TrieHit(const KeyT& key, ValueT& value, std::size_t position) : key_(key), value_(value), position_(position) {}


			const KeyT& getKey() const
			{
				return key_;
			}

			ValueT& getValue() const
			{
				return value_;
			}

			std::size_t getPosition() const
			{
				return position_;
			}

		private:
			KeyT key_;
			ValueReference<ValueT> value_;
			std::size_t position_;
		};

	}
}

#endif