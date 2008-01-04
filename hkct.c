/*
  +----------------------------------------------------------------------+
  | hkct - library for misc. functions                                   |
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

#define	MODULE_RELEASE	"$Revision$"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hkct.h"

#include "apr_env.h"
#include "apr.h"
#include "apr_md5.h"
#include "apr_sha1.h"
#include "apr_strings.h"

#include <stdlib.h>

/* If you declare any globals in php_hkct.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(hkct)
*/

/* True global resources - no need for thread safety here */
static int le_hkct;

/* {{{ hkct_functions[]
 *
 * Every user visible function must have an entry in hkct_functions[].
 */
zend_function_entry hkct_functions[] = {
	PHP_FE(hkct_validate_pw,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in hkct_functions[] */
};
/* }}} */

/* {{{ hkct_module_entry
 */
zend_module_entry hkct_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"hkct",
	hkct_functions,
	PHP_MINIT(hkct),
	PHP_MSHUTDOWN(hkct),
	NULL,
	NULL,
	PHP_MINFO(hkct),
#if ZEND_MODULE_API_NO >= 20010901
	MODULE_RELEASE,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HKCT
ZEND_GET_MODULE(hkct)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("hkct.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_hkct_globals, hkct_globals)
    STD_PHP_INI_ENTRY("hkct.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_hkct_globals, hkct_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_hkct_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_hkct_init_globals(zend_hkct_globals *hkct_globals)
{
	hkct_globals->global_value = 0;
	hkct_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(hkct)
{
	/* If you have INI entries, uncomment these lines
	ZEND_INIT_MODULE_GLOBALS(hkct, php_hkct_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(hkct)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(hkct)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "hkct library", "enabled");
	php_info_print_table_row(2, "Module release", MODULE_RELEASE);
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ proto boolean hkct_validate_pw(string password, sting hash)
validates a password */
PHP_FUNCTION(hkct_validate_pw)
{
	int argc = ZEND_NUM_ARGS();
	char *password = NULL;
	char *hash = NULL;
	int password_len;
	int hash_len;
	unsigned int i = 0;
	char md5str[33];
	unsigned char digest[APR_MD5_DIGESTSIZE];
	apr_md5_ctx_t context;
	char *r;
	apr_status_t status;

	if (zend_parse_parameters(argc TSRMLS_CC, "ss", &password, &password_len, &hash, &hash_len) == FAILURE) {
		return;
	}

	if( hash_len == 32 )
	{
		md5str[0] = '\0';

		apr_md5_init( &context );
		apr_md5_update( &context, password, password_len );
		apr_md5_final( digest, &context );
		for( i = 0, r = md5str; i < 16; i++, r += 2 ) 
		{
			sprintf( r, "%02x", digest[i] );
		}
		*r = '\0';
		
		if( apr_strnatcmp( hash, md5str ) == 0 )
			RETURN_TRUE;
		else
			RETURN_FALSE;
	}
	
	status = apr_password_validate( password, hash );

	if( status == APR_SUCCESS )
	   RETURN_TRUE;
	else
	   RETURN_FALSE;
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
