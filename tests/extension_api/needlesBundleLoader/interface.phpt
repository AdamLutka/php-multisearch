--TEST--
Tests needles bundle loader - interface
--FILE--
<?php
declare(strict_types=1);

use MultiSearch\NeedlesBundleLoader;


var_dump(array_values(class_implements(NeedlesBundleLoader::class)));

--EXPECT--
array(1) {
  [0]=>
  string(40) "MultiSearch\NeedlesBundleLoaderInterface"
}

