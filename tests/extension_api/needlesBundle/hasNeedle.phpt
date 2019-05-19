--TEST--
Tests needles bundle - hasNeedle
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();
$needlesBundle->insert('bar', 'BAR DATA');

var_dump($needlesBundle->hasNeedle('nokey'));
var_dump($needlesBundle->hasNeedle('bar'));

--EXPECT--
bool(false)
bool(true)
