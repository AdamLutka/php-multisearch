--TEST--
Tests needles bundle loader - child
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;
use MultiSearch\NeedlesBundleLoader;

define('FIXTURE_FILEPATH', __DIR__ . '/_fixture.txt');


class NeedlesBundleLoaderChild extends NeedlesBundleLoader
{
	public function loadFromFile(string $filepath): NeedlesBundle
	{
		$bundle = parent::loadFromFile($filepath);
		$bundle->insert('child');

		return $bundle;
	}
}


$loader = new NeedlesBundleLoaderChild();

$needlesBundle = $loader->loadFromFile(FIXTURE_FILEPATH);
foreach ($needlesBundle->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
	echo "\n";
}

--EXPECT--
string(0) ""
string(0) ""

string(5) "child"
string(0) ""

string(7) "k e y 1"
string(11) "v a l u e 1"

string(6) "ke	y
2"
string(11) "multi
	line"

string(7) "onlyKey"
string(0) ""

