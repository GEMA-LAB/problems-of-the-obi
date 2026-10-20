var old_pattern = /^[A-Z]{3}-[0-9]{4}$/;
var new_pattern = /^[A-Z]{3}[0-9][A-Z][0-9]{2}$/;

var plate;
scanf("%s", "plate");

if (old_pattern.test(plate)) {
  printf("1\n");
} else if (new_pattern.test(plate)) {
  printf("2\n");
} else {
  printf("0\n");
}
