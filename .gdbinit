break main

define dish
	disas
	i r
end

document dish
	I wanted to make something that printed rip and the registers at the same time. 
	Maybe this thing will grow into something beautiful. 
end

define xx
	x/64b $arg0
end

define xxh
	x/32x $arg0
end

define di
	si
	si
end