#include "multisearch_exception.h"
#include "common.h"

#include "ext/spl/spl_exceptions.h"


zend_class_entry *multisearch_ce_exception;


static zend_function_entry exception_functions[] = {
	PHP_FE_END
};


void multisearch_register_class_exception()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, MULTISEARCH_CLASSNAME_STR(MultiSearchException), exception_functions);

	multisearch_ce_exception = zend_register_internal_class_ex(&tmp_ce, spl_ce_RuntimeException TSRMLS_CC);
}
