--TEST--
Tests needles bundle - getNeedle
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();
$needlesBundle->insert('bar', 'BAR DATA');

try {
	$needlesBundle->getNeedle('nokey');
}
catch (\Exception $e) {
	var_dump(get_class($e));
	var_dump($e->getMessage());
	echo "\n";
}

$needle = $needlesBundle->getNeedle('bar');

var_dump($needle->getKey());
var_dump($needle->getValue());

--EXPECT--
string(32) "MultiSearch\MultiSearchException"
string(22) "There is no key: nokey"

string(3) "bar"
string(8) "BAR DATA"
