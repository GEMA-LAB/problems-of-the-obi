{ OBI2005            }
{ Tarefa Mini-Poker  }
{ r. anido           }

program minipoker;

var
	cartas		 : array[1..13] of integer;
	i, j, k, n	 : integer;
	min, max		 : integer;
	max_v, max_c : integer;
	max2_v, max2_c : integer;
	pontos		 : integer;

begin				 
	readln(n);
	for i:=1 to n do begin
		pontos := 0;
		max := 0; min := 14;
		max_v := 0; max_c := 0;
		{ vamos contar quantas cartas de cada valor recebemos }
		for j:=1 to 13 do
			cartas[j] := 0;
		for j:=1 to 5 do begin
			read(k);
			cartas[k] := cartas[k]+1;
			{ aproveita para determinar a maior e a menor cartas }
			if k < min then min := k;
			if k > max then max := k;
			if cartas[k] >= max_v then begin
				max_v := cartas[k];
				max_c := k;
			end;
		end;
		readln;
		{ determina a segunda maior carta }
		max2_v := 0; max2_c := 0;
		for j := 1 to 13 do begin
			if (j<>max_c) and (cartas[j]>max2_v) then begin
				max2_v := cartas[j];
				max2_c := j;
			end;
		end;
		{ determina pontuação }
		case max_v of
		  1 : if (max - min) = 4 then
					pontos := 200 + min;
		  2 : if max2_v=2 then begin
					if (max2_c > max_c) then
						pontos := 3*max2_c + 2*max_c + 20
					else
						pontos := 3*max_c + 2*max2_c + 20
				end
				else
						pontos := max_c;
		  3 : if (max2_v = 2) then
					pontos := 160 + max_c
				else
					pontos := 140 + max_c;
		  4 : pontos := 180 + max_c;
		end; { case }
		writeln('Teste ', i);
		writeln(pontos);
		writeln;
	end;
end.
