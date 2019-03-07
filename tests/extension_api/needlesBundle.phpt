--TEST--
Tests needles bundle
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


$searchHits = $needlesBundle->searchIn('arabsky baraba');

var_dump(count($searchHits));
echo "\n";

foreach ($searchHits as $searchHit) {
	var_dump($searchHit->getKey());
	var_dump($searchHit->getValue());
	var_dump($searchHit->getPosition());
	echo "\n";
}

$secondNeedlesBundle = new NeedlesBundle();
$secondNeedlesBundle->insert('key');

var_dump(count($needlesBundle->getNeedles()));
var_dump(count($secondNeedlesBundle->getNeedles()));


echo "\n";

$thirdNeedlesBundle = clone $secondNeedlesBundle;
$thirdNeedlesBundle->insert('third');

var_dump(count($needlesBundle->getNeedles()));
var_dump(count($secondNeedlesBundle->getNeedles()));
var_dump(count($thirdNeedlesBundle->getNeedles()));

--EXPECT--
string(3) "ara"
string(8) "ARA DATA"

string(4) "arab"
string(9) "ARAB DATA"

string(3) "bar"
string(8) "BAR DATA"

string(4) "bars"
string(9) "BARS DATA"

int(5)

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

int(4)
int(1)

int(4)
int(1)
int(2)
