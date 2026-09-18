 var n, resp;

scanf("%d", "n");

resp = 0;

for (var i = 1 ; i <= n ; i++) {
	var a, b;
    scanf("%d %d", "a", "b");

	if (a == 1)
		resp++ ; 
	else
		if(b == 0)
			resp++ ;  
}

printf("%d\n", resp);