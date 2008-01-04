--TEST--
HKCT: hkct_validate_pw - empty hash
--FILE--
<?php

$pwd = 'Test';
$hash = '';

$rc = hkct_validate_pw( $pwd, $hash );

if( $rc == TRUE )
	echo "Validation succeeded.\n";
else
	echo "Validation failed.\n";

?>
--EXPECTF--
PHP Warning:  second parameter must not be empty. in %s/test_004.php on line %d

Warning: second parameter must not be empty. in %s/test_004.php on line %d
Validation failed.
