/*
  +----------------------------------------------------------------------+
  | hkct                                                                 |
  +----------------------------------------------------------------------+
  | Copyright (c) 2008 Helmut K. C. Tessarek                             |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License"); you  |
  | may not use this file except in compliance with the License. You may |
  | obtain a copy of the License at                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Author: Helmut K. C. Tessarek                                        |
  +----------------------------------------------------------------------+
*/

/* $Id */

#ifndef PHP_HKCT_H
#define PHP_HKCT_H

extern zend_module_entry hkct_module_entry;
#define phpext_hkct_ptr &hkct_module_entry

#ifdef PHP_WIN32
#define PHP_HKCT_API __declspec(dllexport)
#else
#define PHP_HKCT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(hkct);
PHP_MSHUTDOWN_FUNCTION(hkct);
PHP_RINIT_FUNCTION(hkct);
PHP_RSHUTDOWN_FUNCTION(hkct);
PHP_MINFO_FUNCTION(hkct);

PHP_FUNCTION(hkct_validate_pw);

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(hkct)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(hkct)
*/

#ifdef ZTS
#define HKCT_G(v) TSRMG(hkct_globals_id, zend_hkct_globals *, v)
#else
#define HKCT_G(v) (hkct_globals.v)
#endif

#endif	/* PHP_HKCT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
