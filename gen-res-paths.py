# This file is part of gtkpoc.

# gtkpoc is free software: you can redistribute it and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation, either version 3
# of the License, or (at your option) any later version.

# gtkpoc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with gtkpoc.
# If not, see <https://www.gnu.org/licenses/>.

import sys
import re

USAGE = "Usage: python3 generate-resource-paths.py <input.xml> <output.[c|h]>"

argc = len(sys.argv)
if (argc != 3):
    sys.exit(f"Expected {2} args but found {argc - 1}\n{USAGE}")

in_path = sys.argv[1]
out_path = sys.argv[2]

in_type = in_path[-4:]
if in_type != ".xml":
    sys.exit(f"Invalid input file type\n{USAGE}")

out_type = out_path[-2:]
if out_type != '.h' and out_type != '.c':
    sys.exit(f"Invalid output file type\n{USAGE}")

is_header = out_type == '.h'

out_lines = []
if is_header:
    out_lines.append("#pragma once\n\n")
else:
    incl_val = out_path[out_path.rfind("/")+1:-2]
    out_lines.append(f"#include \"{incl_val}.h\"\n\n")

with open(in_path, 'r') as file:
    prefix = ""

    for line in file:
        line = line.strip()

        if len(line) >= 11 and line[:11] == "<gresource ":
            first_quote_idx = line.find("\"")
            second_quote_idx = line[first_quote_idx+1:].find("\"") + first_quote_idx + 1
            prefix = line[first_quote_idx+1:second_quote_idx]
        elif len(line) >= 6 and line[:6] == "<file>":
            line = re.sub(r"<file>|</file>", "", line)
            res_filename = line
            line = re.sub(r"[-/.]", "_", line)
            line = line.upper()

            if is_header:
                out_lines.append(f"extern const char *RES_{line};\n")
            else:
                out_lines.append(f"const char *RES_{line} = \"{prefix}/{res_filename}\";\n")

with open(out_path, 'w') as file:
    file.writelines(out_lines)
