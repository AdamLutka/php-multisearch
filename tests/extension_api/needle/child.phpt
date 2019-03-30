--TEST--
Tests needle - child
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\Needle;


class NeedleChild extends Needle
{
	public function __construct(string $key)
	{
		parent::__construct($key, $key);
	}


	public function getKey(): string
	{
		return strtolower(parent::getKey());
	}

	public function getValue(): string
	{
		return strtoupper(parent::getValue());
	}
}

$needle = new NeedleChild('Key');

var_dump($needle->getKey());
var_dump($needle->getValue());

--EXPECT--
string(3) "key"
string(3) "KEY"

