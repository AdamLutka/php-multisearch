--TEST--
Tests needles bundle loader
--FILE--
<?php
declare(strict_types=1);

define('FIXTURE_SOURCE_FILEPATH', __DIR__ . '/needlesBundleLoader.fixture');
define('FIXTURE_FILEPATH', FIXTURE_SOURCE_FILEPATH . '.tmp');

copy(FIXTURE_SOURCE_FILEPATH, FIXTURE_FILEPATH);
touch(FIXTURE_FILEPATH, filemtime(FIXTURE_SOURCE_FILEPATH));



$loader = new MultiSearch\NeedlesBundleLoader();
try {
	$loader->loadNeedlesBundle(FIXTURE_FILEPATH . '.notExists');
}
catch (\Exception $e) {
	var_dump(get_class($e));
	echo "\n";
}


$needlesBundle1 = $loader->loadNeedlesBundle(FIXTURE_FILEPATH);
foreach ($needlesBundle1->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}

$needlesBundle2 = $loader->loadNeedlesBundle(FIXTURE_FILEPATH);
$needlesBundle2->insert('next');

var_dump(count($needlesBundle1->getNeedles()));
var_dump(count($needlesBundle2->getNeedles()));
echo "\n";


file_put_contents(FIXTURE_FILEPATH, "next\tkey", FILE_APPEND);

$needlesBundle3 = $loader->loadNeedlesBundle(FIXTURE_FILEPATH);
foreach ($needlesBundle3->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}


unlink(FIXTURE_FILEPATH);

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

int(4)
int(5)

string(0) ""
string(0) ""

string(7) "k e y 1"
string(11) "v a l u e 1"

string(6) "ke	y
2"
string(11) "multi
	line"

string(4) "next"
string(3) "key"

string(7) "onlyKey"
string(0) ""
