--TEST--
Tests needles bundle repository respects open_basedir
--INI--
open_basedir=/var/
--FILE--
<?php
declare(strict_types=1);

$repository = MultiSearch\NeedlesBundleRepository::getInstance();
try {
	$repository->fromFile('/etc/passwd');
}
catch (\Exception $e) {
	var_dump(get_class($e));
	var_dump($e->getMessage());
}

--EXPECT--
string(32) "MultiSearch\MultiSearchException"
string(49) "Forbidden (open_basedir restriction): /etc/passwd"
