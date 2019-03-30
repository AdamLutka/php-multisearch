--TEST--
Tests needles bundle loader - loadFromFile
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundleLoader;

define('FIXTURE_FILEPATH', __DIR__ . '/_fixture.txt');


$loader = new NeedlesBundleLoader();
try {
	$loader->loadFromFile(FIXTURE_FILEPATH . '.notExists');
}
catch (\Exception $e) {
	var_dump(get_class($e));
	echo "\n";
}


$needlesBundle1 = $loader->loadFromFile(FIXTURE_FILEPATH);
foreach ($needlesBundle1->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}

--EXPECT--
string(32) "MultiSearch\MultiSearchException"

string(0) ""
string(0) ""

string(7) "k e y 1"
string(11) "v a l u e 1"

string(6) "ke	y
2"
string(11) "multi
	line"

string(7) "onlyKey"
string(0) ""
