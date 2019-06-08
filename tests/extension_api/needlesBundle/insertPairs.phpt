--TEST--
Tests needles bundle - insertPairs
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle1 = new NeedlesBundle();
$needlesBundle1->insertPairs([
	1 => 'one',
	'2' => 'two',
	'three' => 'three',
]);
var_dump($needlesBundle1->getPairs());

$needlesBundle2 = new NeedlesBundle();
$needlesBundle2->insertPairs([1,2,3]);
var_dump($needlesBundle2->getPairs());

try {
	$needlesBundle2->insertPairs(['hello world' => []]);
}
catch (\Exception $e) {
	var_dump(get_class($e));
	var_dump($e->getMessage());
}

--EXPECT--
array(3) {
  [1]=>
  string(3) "one"
  [2]=>
  string(3) "two"
  ["three"]=>
  string(5) "three"
}
array(3) {
  [0]=>
  string(1) "1"
  [1]=>
  string(1) "2"
  [2]=>
  string(1) "3"
}
string(32) "MultiSearch\MultiSearchException"
string(33) "Invalid value of key: hello world"

