--TEST--
Tests needles bundle repository
--FILE--
<?php
declare(strict_types=1);

define('FIXTURE_SOURCE_FILEPATH', __DIR__ . '/needlesBundleRepository.fixture');
define('FIXTURE_FILEPATH', FIXTURE_SOURCE_FILEPATH . '.tmp');

copy(FIXTURE_SOURCE_FILEPATH, FIXTURE_FILEPATH);
touch(FIXTURE_FILEPATH, filemtime(FIXTURE_SOURCE_FILEPATH));



$repository = MultiSearch\NeedlesBundleRepository::getInstance();
try {
	$repository->fromFile(FIXTURE_FILEPATH . '.notExists');
}
catch (\Exception $e) {
	var_dump(get_class($e));
	echo "\n";
}


$needlesBundle1 = $repository->fromFile(FIXTURE_FILEPATH);
foreach ($needlesBundle1->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}

$needlesBundle2 = $repository->fromFile(FIXTURE_FILEPATH);
$needlesBundle2->insert('next');

var_dump(count($needlesBundle1->getNeedles()));
var_dump(count($needlesBundle2->getNeedles()));
echo "\n";


file_put_contents(FIXTURE_FILEPATH, "key3\tvalue3", FILE_APPEND);

$needlesBundle3 = $repository->fromFile(FIXTURE_FILEPATH);
foreach ($needlesBundle3->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}


var_dump(count($needlesBundle1->getNeedles()));
var_dump(count($needlesBundle2->getNeedles()));
var_dump(count($needlesBundle3->getNeedles()));

echo "\n";

$repository->dispose($needlesBundle1);

var_dump(count($needlesBundle1->getNeedles()));
var_dump(count($needlesBundle2->getNeedles()));
var_dump(count($needlesBundle3->getNeedles()));


unlink(FIXTURE_FILEPATH);

--EXPECT--
string(32) "MultiSearch\MultiSearchException"

string(4) "key1"
string(6) "value1"

string(4) "key2"
string(6) "value2"

int(2)
int(3)

string(4) "key1"
string(6) "value1"

string(4) "key2"
string(6) "value2"

string(4) "key3"
string(6) "value3"

int(2)
int(3)
int(3)

int(0)
int(3)
int(3)
