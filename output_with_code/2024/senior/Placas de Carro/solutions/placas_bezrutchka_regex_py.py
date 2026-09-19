#!/usr/bin/env python3
import re

old_pattern = "^[A-Z]{3}-[0-9]{4}$"
new_pattern = "^[A-Z]{3}[0-9][A-Z][0-9]{2}$"

plate = input()
if re.match(old_pattern, plate):
  print(1)
elif re.match(new_pattern, plate):
  print(2)
else:
  print(0)
