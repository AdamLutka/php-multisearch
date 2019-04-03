--TEST--
Tests memory persistent storage - interface
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\MemoryPersistentStorage;


var_dump(array_values(class_implements(MemoryPersistentStorage::class)));

--EXPECT--
array(1) {
  [0]=>
  string(41) "MultiSearch\NeedlesBundleStorageInterface"
}

