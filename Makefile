# This is where building happens
wlib = /home/wispy/prj/wlib
inc = $(wlib)/inc
gcc = gcc
lsobj = $(shell find $(wlib)/obj/* -name '*.o' | tr '\n' ' ')
crobj = $(shell $(wlib)/lib.sh $(gcc) $(wlib)/src $(wlib)/obj $(inc))
libdirx = lib
libdir = /usr/lib/

compile:
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c90
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=iso9899:199409
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c99
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c11
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c18
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c2x
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=gnu90
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=gnu99
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=gnu11
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=gnu18
	gcc -c $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=gnu2x
	gcc -E $(C) -Iinc -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=gnu2x | grep -v "#" > test/`basename $(C)`
debug:
	$(call crobj)
	ar -rc $(libdirx)/libwc.a $(call lsobj)
inst:
	sudo mv $(libdirx)/libwc.a $(libdir)
#wos:
#	mkdir -p
#	$(call crobj,.)
#	ar -rc $(libdirx)/li 