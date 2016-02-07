# Copyright 2016 Jonathan Buchanan.
# This file is part of Sunglasses, which is licensed under the MIT License.
# See LICENSE.md for details.\n

import os
import fileinput

bannedDirectories = ["CMakeFiles"]
allowedEndings = [".h", ".cpp", ".vert", ".frag", ".geom", ".pre"]

copyright = '// Copyright 2016 Jonathan Buchanan.\n// This file is part of Sunglasses, which is licensed under the MIT License.\n// See LICENSE.md for details.\n'

for directory, subFolders, files in os.walk("./"):
    if directory not in bannedDirectories:
        for file in files:
            allowed = False
            for ending in allowedEndings:
                if file.endswith(ending):
                    allowed = True
                
                if allowed:
                    inHeader = True
                    filepath = directory + '/' + file
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
