--TEST--
HKCT: hkct_validate_pw - ok
--FILE--
<?php

$pwd = 'Test';

$hashes = array(
        '0cbc6611f5540bd0809a388dc95a615b',
        '$apr1$xWRpS/..$KcdLigTYNOdRdsoTLmWqo0',
        'xWXPfLCmQqfcw',
        '{SHA}ZAqyuuB77cTBY/Z5p0b3q3+10fo='
);

foreach( $hashes as $hash )
{
        $rc = hkct_validate_pw( $pwd, $hash );
        if( $rc == TRUE )
                echo "Validation succeeded.\n";
        else
                echo "Validation failed.\n";
}

?>
--EXPECT--
Validation succeeded.
Validation succeeded.
Validation succeeded.
Validation succeeded.
