program vestib;

var
	i, N, ans: integer;
	gab, can: string;
begin
	readln(N);
	readln(gab);
	readln(can);
	ans := 0;
	for i := 1 to N do
		if gab[i] = can[i] then
			ans := ans + 1;
	writeln(ans);
end.
