program sorvete;

const MAXSORV=10000;

type 
	intervalos = record
		inicio, final: integer;
	end;


var 
	sorveteiros: array [1..MAXSORV] of intervalos;
	tam_praia, num_sorveteiros: integer;
	i, min, max: integer;
	num_teste: integer;


procedure ordena_sorveteiros;
(* ordena sorveteiros por ordem crescente do inicio do trajeto *)
var
	i, j: integer;
	temp: intervalos;
	
begin
	for i:=1 to num_sorveteiros do begin
		j := i;
		while (j > 1) and (sorveteiros[j].inicio < sorveteiros[j-1].inicio) do begin
			temp := sorveteiros[j];
			sorveteiros[j] := sorveteiros[j-1];
			sorveteiros[j-1] := temp;
			j := j-1;
		end
	end
end;


begin
	num_teste := 1;
	read(tam_praia, num_sorveteiros);
	while (tam_praia <> 0) do begin
		for i := 1 to num_sorveteiros do (* Le os intervalos *)
			read(sorveteiros[i].inicio, sorveteiros[i].final);
		ordena_sorveteiros;
		min := sorveteiros[1].inicio;
		max := sorveteiros[1].final;
		writeln('Teste ', num_teste);
		num_teste := num_teste + 1;
		for i := 1 to num_sorveteiros do begin (* processa os intervalos *)
			if (sorveteiros[i].inicio > max) then begin (* imprime intervalo corrente *)
				writeln(min,' ', max);
				min := sorveteiros[i].inicio;
				max := sorveteiros[i].final;
			end
			else if (sorveteiros[i].final > max) then
				max := sorveteiros[i].final;
		end; (* for *)
		writeln(min, ' ', max); (* imprime ultimo intervalo *)
		writeln;
		read(tam_praia, num_sorveteiros);
	end
end.
