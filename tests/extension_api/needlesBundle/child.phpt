--TEST--
Tests needles bundle - child
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundle;


class NeedlesBundleChild extends NeedlesBundle
{
	public function __clone()
	{
		var_dump("cloned");
	}

	public function insert(string $key, string $value = ''): void
	{
		parent::insert(strtoupper($key), $value);
	}

	public function getNeedles(): array
	{
		return array_reverse(parent::getNeedles());
	}
}


$needlesBundle1 = new NeedlesBundleChild();
$needlesBundle1->insert('a');

$needlesBundle2 = clone $needlesBundle1;
$needlesBundle2->insert('b');

var_dump(count($needlesBundle1->getNeedles()));
var_dump(count($needlesBundle2->getNeedles()));

foreach ($needlesBundle2->getNeedles() as $needle) {
	var_dump($needle->getKey());
}

--EXPECT--
string(6) "cloned"
int(1)
int(2)
string(1) "B"
string(1) "A"

