to compile pagesim
>>> gcc -Wall -g pagesim.c LRU.c fifo.c extra.c formatprint.c -o pagesim

to run pagesim object file
>>> ./pagesim 20 page_sim.txt lru

note: replace "lru" with "fifo" or "extra"

to compile pagestats
>>> gcc -Wall -g pagestats.c LRU.c fifo.c extra.c formatprint.c -o pagestats

to run pagestats object file
>>> ./pagestats 5 100 10 page_sim.txt