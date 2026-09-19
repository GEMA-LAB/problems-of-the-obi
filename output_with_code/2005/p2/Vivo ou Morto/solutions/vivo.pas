{ OBI2005        }
{ Tarefa Vivo    }
{ r. anido       }

program vivo;

var
	partic		: array[1..100] of integer;
	i, j, k, n	: integer;
	p, r			: integer;
	ordem, acao	: integer;
	teste			: integer;

begin				 
	readln(p, r);
	teste := 1;
	while (p<>0) do begin
		{ lê participantes }
		for i:=1 to p do
			read(partic[i]);
		readln;
		for i:=1 to r do begin
			read(n, ordem);
			k := 1;
			for j:=1 to n do begin
				read(acao);
				{ procura participante ainda ativo, existe ao menos um }
				while partic[k] = 0 do k := k+1;
				if acao <> ordem then
					partic[k] := 0; { eliminado do jogo! }
				k := k + 1;
			end;
			readln;
		end;
		writeln('Teste ', teste);
		teste := teste + 1;
		{ descobre quem venceu e imprime }
		k := 1;
		while partic[k] = 0 do k := k+1;
		writeln(partic[k]);
		writeln;
		readln(p, r);
	end;
end.
