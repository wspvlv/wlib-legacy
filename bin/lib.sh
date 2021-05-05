# if it ain't broken don't fix it
## it's broken, how we fix it?

[ ! -d "obj/wc/$1" ] && mkdir -p obj/wc/$1
[ ! -d "lib/wc/`echo $1 | cut -d / -f 1`" ] && mkdir -p lib/wc/`echo $1 | cut -d / -f 1`
ls src/wc/$1/*.c | while read F; do gcc -v -Wall -Wextra -Wno-overflow -Wno-char-subscripts -Werror -fmax-errors=1 -I inc -o obj/`echo $F | cut -d / -f 1 --complement - | cut -d . -f 1 -`.o -c $F; done
ar -rc lib/wc/$1.l obj/wc/$1/*.o