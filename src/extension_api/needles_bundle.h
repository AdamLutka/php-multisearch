#ifndef MULTISEARCH_NEEDLES_BUNDLE_H
#define MULTISEARCH_NEEDLES_BUNDLE_H

extern "C" {
	#include "php.h"
}

#include "../aho_corasick/trie.h"
#include <string>
#include <memory>

typedef multisearch::ahocorasick::Trie<std::string, std::string> multisearch_needles_bundle_trie;

extern zend_class_entry *multisearch_ce_needles_bundle;

void multisearch_register_class_needles_bundle();
void multisearch_init_needles_bundle(zval* bundle, const std::shared_ptr<multisearch_needles_bundle_trie>& trie);

#endif
