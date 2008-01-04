--TEST--
HKCT: hkct_validate_pw - empty password
--FILE--
<?php

$pwd = '';

$hashes = array(
        'd41d8cd98f00b204e9800998ecf8427e',
        '$apr1$k8ld./..$SmLNTvSpB8tQ4dWvl7N4l0',
        'k839QdCz0bPfQ',
        '{SHA}2jmj7l5rSw0yVb/vlWAYkK/YBwk='
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
