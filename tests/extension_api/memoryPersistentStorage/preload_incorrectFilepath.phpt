--TEST--
Tests memory persistent storage - preload incorrect filepath
--INI--
multisearch.needles.preload = /tmp/too_small_chance_to_have_file_with_this_name
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\MemoryPersistentStorage;


var_dump(MemoryPersistentStorage::getInstance()->hasNeedlesBundle('/tmp/too_small_chance_to_have_file_with_this_name'));

--EXPECT--
multisearch: needles preload failed '/tmp/too_small_chance_to_have_file_with_this_name'
bool(false)

