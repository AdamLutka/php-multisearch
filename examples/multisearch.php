<?php
	$haystack = file_get_contents(__DIR__ . '/haystack.txt');
	$needlesFilepath = __DIR__ . '/needles.txt';

	$loadTimeStart = microtime(true);
	$loader = new MultiSearch\NeedlesBundleLoader();
	$needles = $loader->loadFromFile($needlesFilepath);
	$loadTimeEnd = microtime(true);

	$buildTimeStart = microtime(true);
	$needles->searchIn('');
	$buildTimeEnd = microtime(true);

	$searchTimeStart = microtime(true);
	$hits = $needles->searchIn($haystack);
	$searchTimeEnd = microtime(true);

	$loadTime = number_format($loadTimeEnd - $loadTimeStart, 6);
	$buildTime = number_format($buildTimeEnd - $buildTimeStart, 6);
	$searchTime = number_format($searchTimeEnd - $searchTimeStart, 6);
	$totalTime = number_format($loadTime + $buildTime + $searchTime, 6);

	echo "Load time:   $loadTime\n";
	echo "Build time:  $buildTime\n";
	echo "Search time: $searchTime\n";
	echo "Total time:  $totalTime\n";
	echo "\n";
	echo "Needles count:   " . count($needles->getNeedles()) . "\n";
	echo "Haystack length: " . strlen($haystack) . "\n";
	echo "Found needles:   " . count($hits) . "\n";

