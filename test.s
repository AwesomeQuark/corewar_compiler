.name "zork"
.comment "just a basic living prog"

l2:  sti %5,%:live,%0
	and	r1,%0,r1
live: live %1
#heil anne frank
		zjmp %:live
