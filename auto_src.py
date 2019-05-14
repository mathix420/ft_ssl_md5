# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    auto_src.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agissing <agissing@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/10 15:37:14 by agissing          #+#    #+#              #
#    Updated: 2019/04/14 18:34:29 by agissing         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys, os, re, glob

HOME=os.getcwd()

if len(sys.argv) != 2:
    exit("Usage :\n\t" + sys.argv[0] + " Makefile_cible")

file = sys.argv[1]
    
if not os.path.isfile(file):
    exit("Bad filename")

fo = open(file, "r")
    
if not fo:
    exit("Error: open fail")

data = fo.read()
fo.close()
    
if not len(data):
    exit("Error: file empty")

results = re.findall(r"((?<=#{{AUTO-SRC})((?!#{END}).*\n)*(?=#{END}))", data)
dd = re.compile(r"((?<=#{{AUTO-SRC})((?!#{END}).*\n)*(?=#{END}))").split(data)


def callback_sub(elem):
    elem = elem.group(0)[12:]
    rule = elem.split('}')[0]
    original_rule = "#{{AUTO-SRC}" + rule + '}'
    infos = dict(item.split("=") for item in rule.split(";"))
    fin = []
    os.chdir(os.path.join(HOME, infos['path']))
    for file in glob.glob(infos['file']):
        fin.append(file)
    return original_rule + "\n" + infos['name'] + " = " + ' \\\n'.join(fin) + "\n#{END}"


out = re.sub(r"(#{{AUTO-SRC}((?!#{END}).*\n)*#{END})", callback_sub, data)

os.chdir(HOME)
fp = open(file, "w+")
fp.write(out)
fp.close()
