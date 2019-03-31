--TEST--
Tests memory persistent storage - clone 
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\MemoryPersistentStorage;
use MultiSearch\MultiSearchException;


try {
	clone MemoryPersistentStorage::getInstance();
} catch (MultiSearchException $e) {
	var_dump($e->getMessage());
}

--EXPECT--
string(41) "MemoryPersistentStorage cannot be cloned."

