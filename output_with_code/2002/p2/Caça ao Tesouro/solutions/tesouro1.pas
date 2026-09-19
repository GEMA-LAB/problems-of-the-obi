{ OBI2002            }
{ Tarefa Tesouro     }
{ r. anido           }

program tesouro;

const
   MAXN	  = 100;
   MAXTOTAL =  10000;
var
   valor	 : array[1..MAXN] of integer;
   possivel	 : array[0..MAXTOTAL] of boolean;
   x, y, n, i, j : integer;
   meta, arca	 : integer;
   v, maxv	 : integer;
   teste	 : integer;
begin
   teste := 1;
   readln(x, y, n);
   while n <> 0 do begin
      writeln('Teste ', teste);
      inc(teste);
      for i:= 0 to MAXTOTAL do
	 possivel[i] := false;

      { le os valores dos objetos, acumulando os valores }
      arca := 0;
      for i:= 1 to n do begin
	 readln(valor[i]);
	 arca := arca + valor[i];
      end;
      { se valor total e' impar, impossivel dividir }
      if not odd(x + y + arca) then begin
	 { calcula meta para um dos primos }
	 meta := ((x + y + arca) div 2) - x;

	 { agora calcula todos os valores possiveis de
	 serem conseguidos } 
	 i := 1; possivel[0] := true;
	 maxv := 0;
	 while (not possivel[meta]) and (i <= n) do begin
	    v := valor[i];
	    for j := maxv downto 0 do
	       if possivel[j] then
		  possivel[v+j] := true;
	    maxv := maxv + v;
	    inc(i);
	 end;
      end;
      if possivel[meta] then writeln('S')
      else writeln('N');
      writeln;
      readln(x, y, n);
   end;
end.
