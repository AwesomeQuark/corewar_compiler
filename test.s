.name "zork"
.comment "just a basic living prog"

l2:		sti r1, %:live, %1
		and 23, r1, r1
live:	live %1
#heil anne frank
		zjmp %:live
