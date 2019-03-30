--TEST--
Tests needles bundle repository - dispose
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundleRepository;
use MultiSearch\NeedlesBundle;

define('FIXTURE_FILEPATH', __DIR__ . '/_fixture.txt');


$repository = NeedlesBundleRepository::getInstance();
$loadedNeedlesBundle = $repository->fromFile(FIXTURE_FILEPATH);
$needlesBundle = new NeedlesBundle();
$needlesBundle->insert('key');

var_dump(count($loadedNeedlesBundle->getNeedles()));
var_dump(count($needlesBundle->getNeedles()));

$repository->dispose($loadedNeedlesBundle);
$repository->dispose($needlesBundle);

var_dump(count($loadedNeedlesBundle->getNeedles()));
var_dump(count($needlesBundle->getNeedles()));

--EXPECT--
int(2)
int(1)
int(0)
int(0)
