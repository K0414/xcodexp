from enum import Enum

#OPCODE = Enum('OPCODE', 'CHAR JMP SPLIT MATCH')

class XRe(object):

    def __init__(self):
        pass

    def convert(self, infix):
        pass

    def compile(self, regexp):
        postfix = self.convert(regexp)


        for c in postfix:


    def match(self):
        pass
