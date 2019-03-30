--TEST--
Tests needles bundle - getNeedles
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();

$needlesBundle->insert('bar', 'BAR DATA');
$needlesBundle->insert('ara', 'ARA DATA');
$needlesBundle->insert('bars', 'BARS DATA');
$needlesBundle->insert('arab', 'ARAB DATA');

foreach ($needlesBundle->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}

--EXPECT--
string(3) "ara"
string(8) "ARA DATA"

string(4) "arab"
string(9) "ARAB DATA"

string(3) "bar"
string(8) "BAR DATA"

string(4) "bars"
string(9) "BARS DATA"

