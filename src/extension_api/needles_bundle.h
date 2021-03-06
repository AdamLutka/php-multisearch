#ifndef MULTISEARCH_NEEDLES_BUNDLE_H
#define MULTISEARCH_NEEDLES_BUNDLE_H

extern "C" {
	#include "php.h"
}

#include "../trie.h"
#include <string>
#include <memory>

using multisearch_needles_bundle_trie = multisearch::trie;
using multisearch_needles_bundle_trie_ptr = multisearch::trie_ptr;

extern zend_class_entry *multisearch_ce_needles_bundle;

void multisearch_register_class_needles_bundle();
void multisearch_needles_bundle_init(zval* bundle, const multisearch_needles_bundle_trie_ptr& trie);
multisearch_needles_bundle_trie_ptr multisearch_needles_bundle_get_trie(zval* bundle);

#endif
