#ifndef MULTISEARCH_AHOC_VALUEREFERENCE_H
#define MULTISEARCH_AHOC_VALUEREFERENCE_H

#include <functional>

namespace multisearch
{
	namespace ahocorasick
	{

		template<typename ValueT>
		class ValueReference
		{
		public:
			ValueReference() : value_(nullValue_) {}
			ValueReference(ValueT& value) : value_(value) {}

			operator ValueT&() const
			{
				return value_;
			}

		private:
			static ValueT nullValue_;

			std::reference_wrapper<ValueT> value_;
		};


		template<typename ValueT>
		ValueT ValueReference<ValueT>::nullValue_;

	}
}

#endif