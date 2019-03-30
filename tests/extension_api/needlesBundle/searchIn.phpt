--TEST--
Tests needles bundle - searchIn
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle = new NeedlesBundle();

$needlesBundle->insert('bar', 'BAR DATA');
$needlesBundle->insert('ara', 'ARA DATA');
$needlesBundle->insert('bars', 'BARS DATA');
$needlesBundle->insert('arab', 'ARAB DATA');


$searchHits = $needlesBundle->searchIn('arabsky baraba');

foreach ($searchHits as $searchHit) {
	var_dump($searchHit->getKey());
	var_dump($searchHit->getValue());
	var_dump($searchHit->getPosition());
	echo "\n";
}

--EXPECT--
string(3) "ara"
string(8) "ARA DATA"
int(0)

string(4) "arab"
string(9) "ARAB DATA"
int(0)

string(3) "bar"
string(8) "BAR DATA"
int(8)

string(3) "ara"
string(8) "ARA DATA"
int(9)

string(4) "arab"
string(9) "ARAB DATA"
int(9)

