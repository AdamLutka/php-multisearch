<?php
	$haystack = file_get_contents(__DIR__ . '/haystack.txt');
	$needlesFilepath = __DIR__ . '/needles.txt';

	$loadTimeStart = microtime(true);
	$words = file($needlesFilepath);
	$loadTimeEnd = microtime(true);

	$searchTimeStart = microtime(true);
	$hits = 0;
	foreach ($words as $word) {
		$word = rtrim($word, "\n");
		$offset = 0;
		while (($offset = strpos($haystack, $word, $offset + 1)) !== false) {
			++$hits;
		}
	}
	$searchTimeEnd = microtime(true);

	$loadTime = number_format($loadTimeEnd - $loadTimeStart, 6);
	$searchTime = number_format($searchTimeEnd - $searchTimeStart, 6);
	$totalTime = number_format($loadTime + $searchTime, 6);

	echo "Load time:   $loadTime\n";
	echo "Search time: $searchTime\n";
	echo "Total time:  $totalTime\n";
	echo "\n";
	echo "Needles count:   " . count($words) . "\n";
	echo "Haystack length: " . strlen($haystack) . "\n";
	echo "Found needles:   $hits\n";

