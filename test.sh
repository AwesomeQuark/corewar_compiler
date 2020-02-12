#! /bin/sh

./utils/vm_champs/asm test.s > /dev/null & echo done asm
./asm -src test.s -dest test_mine.cor > /dev/null & echo done mine asm
hexdump test.cor > b & echo done hexdump
hexdump test_mine.cor > a & echo done hexdump mine asm
rm test.cor test_mine.cor & echo cleaning
diff a b & echo diff
