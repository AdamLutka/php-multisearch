--TEST--
Tests search hit
--FILE--
<?php
declare(strict_types=1);

$searchHit = new MultiSearch\SearchHit(10, 'key', 'value');

var_dump($searchHit->getPosition());
var_dump($searchHit->getKey());
var_dump($searchHit->getValue());
var_dump($searchHit->getPosition());
var_dump($searchHit->getKey());
var_dump($searchHit->getValue());

echo "\n";

$searchHitNoValue = new MultiSearch\SearchHit(20, 'key2');

var_dump($searchHitNoValue->getPosition());
var_dump($searchHitNoValue->getKey());
var_dump($searchHitNoValue->getValue());

--EXPECT--
int(10)
string(3) "key"
string(5) "value"
int(10)
string(3) "key"
string(5) "value"

int(20)
string(4) "key2"
string(0) ""
