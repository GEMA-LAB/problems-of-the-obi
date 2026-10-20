var maxn = 10100;

var n,m;
scanf("%d%d","n","m");

var ans = [Math.min(n,maxn)];
var v = [m];


for(var i=0; i<Math.min(n,maxn); i++)
   ans[i] = i;

for(var i=0;i<m;i++)
	scanf("%d","v[i]");

for(var i=m-1;i>=0;i--)
   for(var j=0;j<Math.min(n,maxn) && ans[j] < n;j++)
      ans[j] += Math.floor(ans[j] / (v[i]-1));


for(var i=0;i<Math.min(n,10000) && ans[i] < n;i++)
    printf("%d\n",ans[i]+1);
