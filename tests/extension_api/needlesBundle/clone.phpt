--TEST--
Tests needles bundle - clone
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


$needlesBundle1 = new NeedlesBundle();
$needlesBundle1->insert('key');

$needlesBundle2 = new NeedlesBundle();
$needlesBundle2->insert('key');

$clonedNeedlesBundle = clone $needlesBundle1;
$clonedNeedlesBundle->insert('key2');


var_dump(count($needlesBundle1->getNeedles()));
var_dump(count($needlesBundle2->getNeedles()));
var_dump(count($clonedNeedlesBundle->getNeedles()));

--EXPECT--
int(1)
int(1)
int(2)

