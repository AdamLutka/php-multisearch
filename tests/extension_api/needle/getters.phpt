--TEST--
Tests needle - getters
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\Needle;

$needle = new Needle('key', 'value');

var_dump($needle->getKey());
var_dump($needle->getValue());
var_dump($needle->getKey());
var_dump($needle->getValue());

echo "\n";

$needleNoValue = new MultiSearch\Needle('key2');

var_dump($needleNoValue->getKey());
var_dump($needleNoValue->getValue());

--EXPECT--
string(3) "key"
string(5) "value"
string(3) "key"
string(5) "value"

string(4) "key2"
string(0) ""
