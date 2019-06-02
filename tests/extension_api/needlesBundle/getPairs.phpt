--TEST--
Tests needles bundle - getPairs
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();

var_dump($needlesBundle->getPairs());

$needlesBundle->insert('bar', 'BAR DATA');
$needlesBundle->insert('ara', 'ARA DATA');
$needlesBundle->insert('bars', 'BARS DATA');
$needlesBundle->insert('arab', 'ARAB DATA');

var_dump($needlesBundle->getPairs());

--EXPECT--
array(0) {
}
array(4) {
  ["ara"]=>
  string(8) "ARA DATA"
  ["arab"]=>
  string(9) "ARAB DATA"
  ["bar"]=>
  string(8) "BAR DATA"
  ["bars"]=>
  string(9) "BARS DATA"
}

