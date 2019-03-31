--TEST--
Tests memory persistent storage - preload respect open_basedir
--INI--
open_basedir=/too_small_chance_to_have_directory_with_this_name/
multisearch.needles.preload = tests/extension_api/memoryPersistentStorage/_fixture.txt
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\MemoryPersistentStorage;


var_dump(MemoryPersistentStorage::getInstance()->hasNeedlesBundle('tests/extension_api/memoryPersistentStorage/_fixture.txt'));

--EXPECT--
multisearch: needles preload forbidden (open_basedir restriction) 'tests/extension_api/memoryPersistentStorage/_fixture.txt'
bool(false)

