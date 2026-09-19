{ OBI2005            }
{ Tarefa Desculpa    }
{ r. anido           }

program desculpa;

const MAX = 1001;
var
	i, j		  : integer;
	c, f, n, d : integer;
	cartao	  : array[1..MAX] of integer;
	num_teste  : integer;

begin
	num_teste := 0;
	readln(c, f);
	while (c<>0) do begin
		{ inicializa }
		for i:= 1 to c+1 do cartao[i]:=0;
		{ le frases e computa o numero de desculpas na melhor combinacao }
		for i:= 1 to f do begin
			readln(n, d);
			for j:=c+1 downto n+1 do begin
				if (cartao[j-n] + d) > cartao[j] then
					cartao[j] := cartao[j-n] + d;
			end;
		end;
		num_teste := num_teste + 1;
		writeln('Teste ', num_teste);
		writeln(cartao[c+1]);
		writeln;
		readln(c, f);
	end;
end.
