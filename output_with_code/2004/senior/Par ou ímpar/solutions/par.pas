{ OBI2004             }
{ Tarefa Par ou Impar }
{ r. anido            }

program par;

var
   n, i, teste, val1, val2 : integer;
   jogador1, jogador2	   : string[15];
begin
   teste := 1;
   { le numero de jogadas }
   readln(n);
   while n > 0 do begin
      writeln('Teste ', teste);
      inc(teste);
      { le nomes dos jogadores }
      readln(jogador1);
      readln(jogador2);
      for i:=1 to n do begin
	 { le maos dos jogadores }
	 readln(val1, val2);
	 if ((val1+val2) mod 2) = 0 then
	    writeln(jogador1)
	 else
	    writeln(jogador2);
      end;
      writeln;
      { le novo numero de jogadas }
      readln(n);
   end;
end.
