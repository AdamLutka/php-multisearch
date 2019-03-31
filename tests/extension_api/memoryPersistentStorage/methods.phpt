--TEST--
Tests memory persistent storage - methods
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\MemoryPersistentStorage;
use MultiSearch\NeedlesBundle;


$storage = MemoryPersistentStorage::getInstance();

$needlesBundle = new NeedlesBundle();
$needlesBundle->insert('key');

$storage->setNeedlesBundle('needle', $needlesBundle, 10);

var_dump($storage->getNeedlesBundle('needle')->getNeedles()[0]->getKey());
var_dump($storage->getNeedlesBundle('needle', 10)->getNeedles()[0]->getKey());
try {
	var_dump($storage->getNeedlesBundle('needle', 20) === null);
} catch (MultiSearch\MultiSearchException $e) {
	var_dump($e->getMessage());
}

var_dump($storage->hasNeedlesBundle('needle'));
var_dump($storage->hasNeedlesBundle('needle', 10));
var_dump($storage->hasNeedlesBundle('needle', 20));

$storage->removeNeedlesBundle('needle');

var_dump($storage->hasNeedlesBundle('needle'));

--EXPECT--
string(3) "key"
string(3) "key"
string(68) "No needles bundle with name 'needle' and validity stamp at least 20."
bool(true)
bool(true)
bool(false)
bool(false)

