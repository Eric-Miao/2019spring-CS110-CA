the page fault in ex2 in caused mainly because there are not enough room in PT to hold two or more page at the same time. thus each time a new page is wanted, PT didn't cache it so there is a page fault.

at the same time, each page frame in PM only hold one page at one access, relate to one row in PT.

so the page fault will reduce if we can load more pages from HD in to PM each time a page fault happens. and change multiple row in PT at one page access.

to decrase page fault, is to decrease the change in PAGE TABLE when we already have rows with valid bit1. 
MOST easy way we can increase the PM to 8+ pages' size, so that the PM can store all the pages we want to access, in this case from 0-7. then when we again accessing 0&1, there r two page hit.
