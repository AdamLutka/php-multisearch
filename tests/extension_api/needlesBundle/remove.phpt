--TEST--
Tests needles bundle - remove 
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();
$needlesBundle->insert('key1');
$needlesBundle->insert('key2');

var_dump($needlesBundle->remove('key1'));

var_dump($needlesBundle->hasNeedle('key1'));
var_dump($needlesBundle->hasNeedle('key2'));

--EXPECT--
bool(true)
bool(false)
bool(true)

