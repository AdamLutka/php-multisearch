--TEST--
Tests with bigger data and UTF8
--FILE--
<?php
declare(strict_types=1);

define('FIXTURE_NEEDLES_FILEPATH', __DIR__ . '/perf.fixture.needles');
define('FIXTURE_HAYSTACK_FILEPATH', __DIR__ . '/perf.fixture.haystack');
define('FIXTURE_RESULT_FILEPATH', __DIR__ . '/perf.fixture.result');


$loader = new MultiSearch\NeedlesBundleLoader();

$t = microtime(true);
$needles = $loader->loadFromFile(FIXTURE_NEEDLES_FILEPATH);
$loadTime = microtime(true) - $t;

$t = microtime(true);
$needles->searchIn('');
$buildTime = microtime(true) - $t;

$haystack = file_get_contents(FIXTURE_HAYSTACK_FILEPATH);

$t = microtime(true);
$hits = $needles->searchIn($haystack);
$searchTime = microtime(true) - $t;

var_dump(count($hits));

$lines = file(FIXTURE_RESULT_FILEPATH); 
for ($i = 0; $i < count($lines); ++$i) {
	$expectedLine = rtrim($lines[$i], "\n");
	$actualLine = $hits[$i]->getKey() . ' ' . $hits[$i]->getPosition();

	if ($expectedLine !== $actualLine) {
		echo "Expected line ($expectedLine) isn't equal to actual line ($actualLine)";
		break;
	}
}

//var_dump($loadTime, $buildTime, $searchTime);

--EXPECT--
int(479)
