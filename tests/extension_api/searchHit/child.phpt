--TEST--
Tests search hit - child
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\SearchHit;


class SearchHitChild extends SearchHit
{
	public function __construct(int $position, string $key)
	{
		parent::__construct($position + 1, $key, $key);
	}


	public function getPosition(): int
	{
		return parent::getPosition() * 1000;
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

$searchHit = new SearchHitChild(0, 'Key');

var_dump($searchHit->getPosition());
var_dump($searchHit->getKey());
var_dump($searchHit->getValue());

--EXPECT--
int(1000)
string(3) "key"
string(3) "KEY"

