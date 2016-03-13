# Copyright 2016 Jonathan Buchanan.
# This file is part of Sunglasses, which is licensed under the MIT License.
# See LICENSE.md for details.\n

import os
import fileinput

bannedDirectories = ["CMakeFiles", "googlemock", "googletest", ".git"]
allowedEndings = [".h", ".hpp", ".cpp", ".m", ".s", ".v", ".f", ".g", ".vert", ".frag", ".geom", ".pre"]

copyright = '// Copyright 2016 Jonathan Buchanan.\n// This file is part of Sunglasses, which is licensed under the MIT License.\n// See LICENSE.md for details.\n'

for directory, subFolders, files in os.walk("./"):
    directories = directory.split("/");
    allowedDirectory = True;
    for _directory in directories:
        if _directory in bannedDirectories:
            allowedDirectory = False
            break
    if allowedDirectory:
        for file in files:
            allowed = False
            for ending in allowedEndings:
                if file.endswith(ending):
                    allowed = True
            if allowed:
                inHeader = True
                filepath = directory + '/' + file
                print(filepath)
                for line in fileinput.input(filepath, inplace = True, backup = False):
                    if line.startswith('//') and inHeader:
                        continue
                    else:
                        print(line, end = '')
                        inHeader = False
                for lineNumber, line in enumerate(fileinput.input(filepath, inplace = True, backup = False)):
                    if lineNumber == 0:
                        print(copyright, end = '')
                        print(line, end = '')
                    else:
                        print(line, end = '')
