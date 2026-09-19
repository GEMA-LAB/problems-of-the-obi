{ OBI2005                     }
{ Tarefa Campo de Minhocas    }
{ r. anido                    }

program minhoca;

const
	MAXLIN = 100;
	MAXCOL = 100;
var
	i, j, m, n	 : integer;
	campo			 : array [1..MAXLIN, 1..MAXCOL] of integer;
	tot, tot_max : longint;
begin
	{ le campo }
	readln(n, m);
	for i:=1 to n do begin
		for j:=1 to m do begin
			read(campo[i,j]);
		end;
		readln;
	end;
	tot_max := 0;
	{ processa linhas }
	for i:=1 to n do begin
		tot := 0;
		for j:=1 to m do begin
			tot := tot + campo[i,j];
		end;
		if tot > tot_max then tot_max := tot;
	end;
	{ processa colunas }
	for i:=1 to m do begin
		tot := 0;
		for j:=1 to n do begin
			tot := tot + campo[j,i];
		end;
		if tot > tot_max then tot_max := tot;
	end;
	{ imprime o resultado }
	writeln(tot_max);
end.
