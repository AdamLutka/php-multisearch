# PHP-multisearch

PHP 7 extension which enables efficient multiple strings search. It uses [Aho-Corasick algorithm](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm) so the time complexity of the algorithm is linear in the length of the strings plus the length of the searched text plus the number of output matches.

```
<?php
$needlesBundle = new MultiSearch\NeedlesBundle();
$needlesBundle->insert('key', 'value');
$needlesBundle->insert('key2', 'value2');
$needlesBundle->insert('key3');

$hits = $needlesBundle->searchIn('Haystack contains key3.');

var_dump($hits[0]->getKey());        // string(3) "key"
var_dump($hits[0]->getValue());      // string(5) "value"
var_dump($hits[0]->getPosition());   // int(18)

var_dump($hits[1]->getKey());        // string(4) "key3"
var_dump($hits[1]->getValue());      // string(0) ""
var_dump($hits[1]->getPosition());   // int(18)
```

Consider following use case. You have file with relatively static set of terms which you want to search frequently. For example blacklist of words for user statuses on your social network. If you use php-fpm then most of the work is done only once during first request and all following requests during worker lifetime use datastructure from memory.
**NeedlesBundleRepository isn't thread-safe.**

```
<?php
$repository = MultiSearch\NeedlesBundleRepository::getInstance();
$needlesBundle = $repository->fromFile('file_with_strings.txt');
foreach ($needlesBundle->getNeedles() as $needle) {
	var_dump($needle->getKey());
}
```

You can see more examples in [tests](tests/extension_api/).

## Getting Started

### Prerequisites

Build enviroment is prepared in [docker](https://docs.docker.com/install/). Multisearch extension isn't coupled to docker anyhow so you can build it manually but it's easier to use prepared solution.

### Installing

Run make to build and run docker container which builds extension and also runs tests. Builded extension is placed in **build/output** directory.

```
make
```

Find out where directory with extensions is located.

```
php -i | grep extension_dir
```

Copy **build/output/multisearch.so** to extensions directory.

Add extension to your PHP (enable in CLI, php-fpm or both).

```
cp config/multisearch.ini /etc/php/7.1/mods-available/
ln -s -T /etc/php/7.1/mods-available/multisearch.ini /etc/php/7.1/cli/conf.d/30-multisearch.ini  # CLI
ln -s -T /etc/php/7.1/mods-available/multisearch.ini /etc/php/7.1/fpm/conf.d/30-multisearch.ini  # php-fpm
```

Test that extension is loaded in CLI.

```
php --ri multisearch
```

### Configuration

The extension configuration is inside [INI file](config/multisearch.ini).


## Needles bundle file format

Needles can be stored in a file like the following one:

```
key1	value1
k\ne\ty\n2	va\nlu\te2
key3
key4	value4
```

Each line represents one needle. Everything from the begining of line to the first tab character is key (string that is searched in a haystack). The rest of line is value which can be omitted. You can use escape sequences **\t** and **\n** if key or value contain tab or new line character.
