# uwufy
fastest **cross-architecture** text uwuifier in the west, on x86-64 CPUs with
 SSE4.1 it's about 50% as fast as
 [Daniel-Liu-c0deb0t/uwu](https://github.com/Daniel-Liu-c0deb0t/uwu)
, but this one works on **all** platforms. Even on a
 [toaster](https://www.embeddedarm.com/blog/netbsd-toaster-powered-by-the-ts-7200-arm9-sbc/)
, bet you that
 [Daniel-Liu-c0deb0t/uwu](https://github.com/Daniel-Liu-c0deb0t/uwu)
 can't do that.

## How to?
Just pipe a file into the program and see the results.
```sh
./uwufy < ./tests/test_10k.txt > out.txt
```

## Rules
Here are the rules.
1. replace `na` -> `nya`
2. replace `l` and `r` with `w`
3. remove double `l` or `r`
4. add text emoji randomly after punctuation (`.`, `!`)
5. everything must be lowercase
6. stutter at the start of sentences sometimes, only alphabetical chars

## License
[GPL-3.0-or-later](./LICENSE)
