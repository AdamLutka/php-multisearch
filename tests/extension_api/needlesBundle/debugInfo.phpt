--TEST--
Tests needles bundle - debug info
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();
$needlesBundle->insert('key1', 'value1');
$needlesBundle->insert('key2', 'value2');

print_r($needlesBundle);

--EXPECT--
MultiSearch\NeedlesBundle Object
(
    [nodesCount] => 6
    [size] => 500
    [pairs] => Array
        (
            [key1] => value1
            [key2] => value2
        )

)

