--TEST--
Tests memory persistent storage - preload
--INI--
multisearch.needles.preload = tests/extension_api/memoryPersistentStorage/_fixture.txt
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\MemoryPersistentStorage;


$storage = MemoryPersistentStorage::getInstance();
$needlesBundle = $storage->getNeedlesBundle('tests/extension_api/memoryPersistentStorage/_fixture.txt');

foreach ($needlesBundle->getNeedles() as $needle) {
	var_dump($needle->getKey());
	var_dump($needle->getValue());
}

--EXPECT--
string(4) "key1"
string(6) "value1"
string(4) "key2"
string(6) "value2"

