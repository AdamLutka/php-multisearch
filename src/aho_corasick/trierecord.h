#ifndef MULTISEARCH_TRIERECORD_H
#define MULTISEARCH_TRIERECORD_H

#include "valuereference.h"

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename KeyT, typename ValueT>
		class TrieRecord
		{
		public:
			TrieRecord() {}
			TrieRecord(const KeyT& key, ValueT& value) : key_(key), value_(value) {}


			const KeyT& getKey() const
			{
				return key_;
			}

			ValueT& getValue() const
			{
				return value_;
			}

		private:
			KeyT key_;
			ValueReference<ValueT> value_;
		};

	}
}

#endif