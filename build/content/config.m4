PHP_ARG_ENABLE(multisearch, whether to enable MultiSearch support,
[  --enable-multisearch   Enable MultiSearch support])

if test "$PHP_MULTISEARCH" != "no"; then
	export CPPFLAGS="$CPPFLAGS $INCLUDES -std=c++11"

	AC_DEFINE(HAVE_MULTISEARCH, 1, [Whether you have MultiSearch])
	AC_LANG_CPLUSPLUS
	PHP_REQUIRE_CXX
	PHP_SUBST(MULTISEARCH_SHARED_LIBADD)
	PHP_ADD_LIBRARY(stdc++, 1, MULTISEARCH_SHARED_LIBADD)
	PHP_NEW_EXTENSION(multisearch, src/multisearch.cpp src/extension_api/bundles_loader.cpp src/extension_api/multisearch_exception.cpp src/extension_api/needle.cpp src/extension_api/needles_bundle.cpp src/extension_api/search_hit.cpp, $ext_shared)
fi
