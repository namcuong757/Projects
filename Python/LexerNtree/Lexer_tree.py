from tkinter import *
#from tkmacosx import Button
from turtle import width
import re

inToken = ("empty", "empty")


class LexGUI:

    def __init__(self, root):
        self.counter = 0
        self.master = root
        self.master.title("Lexer for TinyPie")
        # first setup
        self.input_code = Label(self.master, text="Source Code: ")
        self.input_code.grid(row=0, column=0, sticky=W, padx=35, pady=5)

        self.input_txt = Text(self.master, height=18,
                              width=35, font=("Calibri", 15))
        self.input_txt.grid(row=1, column=0, sticky=W, padx=35, pady=5)
        self.input_txt.config(
            highlightbackground="ORANGE", highlightthickness=1)

        self.input_counter = Label(
            self.master, text="Current Processing Line: ")
        self.input_counter.grid(row=2, column=0, sticky=W, padx=35)

        self.counter_entry = Entry(self.master, width=2)
        self.counter_entry.grid(row=2, column=0, sticky=E, padx=200)
        self.counter_entry.config({"background": "YELLOW"})
        self.counter_entry.delete(0, END)
        self.counter_entry.insert(0, self.counter)
        # next line button
        self.next_button = Button(
            self.master, text="Next Line", bg='BLUE', fg='WHITE', command=self.next_line)
        self.next_button.grid(row=3, column=0, sticky=W, padx=35, pady=5)
        # second setup
        self.output_code = Label(self.master, text="Tokens: ")
        self.output_code.grid(row=0, column=1, sticky=W, padx=35, pady=1)

        self.output_txt = Text(self.master, height=18,
                               width=35, font=("Calibri", 15))
        self.output_txt.grid(row=1, column=1, sticky=W, padx=35, pady=1)
        self.output_txt.config(
            highlightbackground="BLUE", highlightthickness=1)
        # third setup
        self.tree_label = Label(self.master, text="Parse Tree")
        self.tree_label.grid(row=0, column=2, sticky=W, padx=35, pady=1)

        self.tree_txt = Text(self.master, height=18,
                             width=45, font=("Calibri", 15))
        self.tree_txt.grid(row=1, column=2, sticky=W, padx=35, pady=1)
        self.tree_txt.config(
            highlightbackground="YELLOW", highlightthickness=1)
        # quit button
        self.quit_button = Button(
            self.master, text="Exit", bg='BLUE', fg='WHITE', command=quit)
        self.quit_button.grid(row=3, column=1, sticky=E, padx=35, pady=5)

    def next_line(self):
        splitted_lis = []
        input = self.input_txt.get("1.0", END)
        if(input):
            splitted_lis = input.splitlines()
            MyTokens = self.cutonelinetokens(splitted_lis[self.counter])
            for j in MyTokens:
                self.output_txt.insert(INSERT, j + "\n")
            self.counter += 1
            self.counter_entry.delete(0, END)
            self.counter_entry.insert(0, self.counter)
            # parse tree
            MyTokens = self.tokenlize(MyTokens)
            self.tree_txt.insert(
                INSERT, "###Parse Tree for line " + str(self.counter) + "##")
            self.parser(MyTokens)
            if (self.counter >= len(splitted_lis)):
                text = "\n**End of code**.\n"
                self.tree_txt.insert(INSERT, text)
                self.counter = 0

    def cutonelinetokens(self, string):
        result = []
        string = string.lstrip()
        while(string):
            keyw_reg = re.compile(r"(\bif\b)|(\belse\b)|(\bfloat\b)|(\bint\b)")
            ope_reg = re.compile(r"\+|\*|=|>")
            sep_reg = re.compile(r"\(|\)|:|\"|;|\“|\”")
            id_reg = re.compile(r"([A-Za-z]+\d+)|([A-Za-z]+)")
            int_reg = re.compile(r"(?<![\d.])[0-9]+(?![\d.])")
            float_reg = re.compile(r"\d+\.\d+")
            string_reg = re.compile(r'^[\w\s\d]+(?=”)')

            keyw_token = keyw_reg.match(string)
            ope_token = ope_reg.match(string)
            sep_token = sep_reg.match(string)
            id_token = id_reg.match(string)
            int_token = int_reg.match(string)
            float_token = float_reg.match(string)
            string_token = string_reg.match(string)
            # keyword
            if(keyw_token != None):
                new_string = "<keyword, " + keyw_token.group(0) + ">"
                result.append(new_string)
                string = string.replace(keyw_token.group(0), ' ', 1)
                string = string.lstrip()
            # operator
            elif(ope_token != None):
                new_string1 = "<operator, " + ope_token.group(0) + ">"
                result.append(new_string1)
                string = string.replace(ope_token.group(0), ' ', 1)
                string = string.lstrip()
            # seperator
            elif(sep_token != None):
                new_string2 = "<seperator, " + sep_token.group(0) + ">"
                result.append(new_string2)
                string = string.replace(sep_token.group(0), ' ', 1)
                string = string.lstrip()
            # string lit
            elif(string_token != None):
                new_string6 = "<string, " + string_token.group(0) + ">"
                result.append(new_string6)
                string = string.replace(string_token.group(0), '', 1)
                string = string.lstrip()
            # identifier
            elif(id_token != None):
                new_string3 = "<identifier, " + id_token.group(0) + ">"
                result.append(new_string3)
                string = string.replace(id_token.group(0), '', 1)
                string = string.lstrip()
            # integer lit
            elif(int_token != None):
                new_string4 = "<integer, " + int_token.group(0) + ">"
                result.append(new_string4)
                string = string.replace(int_token.group(0), '', 1)
                string = string.lstrip()
            # float lit
            elif(float_token != None):
                new_string5 = "<float, " + float_token.group(0) + ">"
                result.append(new_string5)
                string = string.replace(float_token.group(0), '', 1)
                string = string.lstrip()
            else:
                print("Cannot process input: ")
                print(string)
                string = ""
        return result

    def tokenlize(self, list):
        result = []
        for i in list:
            tokens = []
            i = i[:-1]
            i = i.replace("<", "")
            i = i.replace(",", "")
            tokens = i.split()
            result.append(tokens)
        return result

    def accept_token(self, Mytokens):
        global inToken
        self.tree_txt.insert(
            INSERT, "     accept token from the list:"+inToken[1] + "\n")
        inToken = Mytokens.pop(0)

    def multi(self, Mytokens):
        self.tree_txt.insert(
            INSERT, "\n----parent node mulity, finding children nodes:" + "\n")
        global inToken
        if(inToken[0] == "float"):
            self.tree_txt.insert(INSERT, "child node (internal): float" + "\n")
            self.tree_txt.insert(
                INSERT, "   multi has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        elif (inToken[0] == "integer"):
            self.tree_txt.insert(INSERT, "child node (internal): int" + "\n")
            self.tree_txt.insert(
                INSERT, "   multi has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)

            if(inToken[1] == "*"):
                self.tree_txt.insert(
                    INSERT, "child node (token):"+inToken[1] + "\n")
                self.accept_token(Mytokens)

                self.tree_txt.insert(
                    INSERT, "child node (internal): multi" + "\n")
                self.multi(Mytokens)
            else:
                self.tree_txt.insert(
                    INSERT, "error, you need * after the int in the math" + "\n")

        else:
            self.tree_txt.insert(
                INSERT, "error, multi expects float or int" + "\n")

    def math(self, Mytokens):
        self.tree_txt.insert(
            INSERT, "\n----parent node math, finding children nodes:" + "\n")
        global inToken
        self.multi(Mytokens)
        if(inToken[1] == "+"):
            self.tree_txt.insert(
                INSERT, "child node (token) of Math:"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        self.multi(Mytokens)

    def exp(self, Mytokens):
        self.tree_txt.insert(
            INSERT, "\n----parent node exp, finding children nodes:" + "\n")
        global inToken
        typeT, token = inToken
        if(typeT == "keyword"):
            self.tree_txt.insert(
                INSERT, "child node (internal): keyword" + "\n")
            self.tree_txt.insert(
                INSERT, "   keyword has child node (token):"+token + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect identifier as the first element of the expression!\n" + "\n")
            return
        if(inToken[0] == "identifier"):
            self.tree_txt.insert(
                INSERT, "child node (internal): identifier" + "\n")
            self.tree_txt.insert(
                INSERT, "   identifier has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect identifier as the second element of the expression!\n" + "\n")
            return

        if(inToken[1] == "="):
            self.tree_txt.insert(
                INSERT, "child node (token):"+inToken[1] + "\n")
            self.tree_txt.insert(
                INSERT, "   keyword has child node (token):"+token + "\n")
            self.accept_token(Mytokens)
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect = as the second element of the expression!" + "\n")
            return

        self.tree_txt.insert(INSERT, "Child node (internal): math" + "\n")
        self.math(Mytokens)

    def comparison_exp(self, Mytokens):
        global inToken
        self.tree_txt.insert(
            INSERT, "\n----parent node comparison_exp, finding children nodes:" + "\n")
        if(inToken[0] == "identifier"):
            self.tree_txt.insert(
                INSERT, "child node (internal): identifier" + "\n")
            self.tree_txt.insert(
                INSERT, "   comparison_exp has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect identifier as the first element of the comparison_exp!\n" + "\n")
            return
        if(inToken[1] == ">"):
            self.tree_txt.insert(
                INSERT, "child node (internal): operator" + "\n")
            self.tree_txt.insert(
                INSERT, "   comparison_exp has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        if(inToken[0] == "identifier"):
            self.tree_txt.insert(
                INSERT, "child node (internal): identifier" + "\n")
            self.tree_txt.insert(
                INSERT, "   comparison_exp has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect identifier as the first element of the comparison_exp!\n" + "\n")
            return

    def if_exp(self, Mytokens):
        global inToken
        self.tree_txt.insert(
            INSERT, "\n----parent node if_exp, finding children nodes:" + "\n")
        if(inToken[1] == "if"):
            self.tree_txt.insert(
                INSERT, "child node (internal): keyword" + "\n")
            self.tree_txt.insert(
                INSERT, "   comparison_exp has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect if as the first element of the if_exp!\n" + "\n")
        if(inToken[1] == "("):
            self.tree_txt.insert(
                INSERT, "child node (internal): operator" + "\n")
            self.tree_txt.insert(
                INSERT, "   comparison_exp has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect ( as the second element of the if_exp!\n")
        self.comparison_exp(Mytokens)
        if(inToken[1] == ")"):
            self.tree_txt.insert(
                INSERT, "child node (internal): operator" + "\n")
            self.tree_txt.insert(
                INSERT, "   comparison_exp has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect ) as the second element of the if_exp!\n" + "\n")

    def string(self, Mytokens):
        global inToken
        self.tree_txt.insert(INSERT, inToken)
        self.tree_txt.insert(
            INSERT, "\n----parent node string, finding children nodes:" + "\n")
        if(inToken[1] == '“'):
            self.tree_txt.insert(
                INSERT, "child node (internal): seperator" + "\n")
            self.tree_txt.insert(
                INSERT, "   self.tree_txt.insert(INSERT,_expr has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        if(inToken[0] == "string"):
            self.tree_txt.insert(
                INSERT, "child node (internal): string lit" + "\n")
            self.tree_txt.insert(
                INSERT, "   self.tree_txt.insert(INSERT,_expr has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        if(inToken[1] == '”'):
            self.tree_txt.insert(
                INSERT, "child node (internal): seperator" + "\n")
            self.tree_txt.insert(
                INSERT, "   self.tree_txt.insert(INSERT,_expr has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)

    def print_expr(self, Mytokens):
        global inToken
        self.tree_txt.insert(
            INSERT, "\n----parent node self.tree_txt.insert(INSERT,_expr, finding children nodes:" + "\n")
        if(inToken[0] == "identifier"):
            self.tree_txt.insert(
                INSERT, "child node (internal): identifier" + "\n")
            self.tree_txt.insert(
                INSERT, "   self.tree_txt.insert(INSERT,_expr has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect identifier as the first element of the comparison_exp!\n" + "\n")
            return
        if(inToken[1] == "("):
            self.tree_txt.insert(
                INSERT, "child node (internal): seperator" + "\n")
            self.tree_txt.insert(
                INSERT, "   self.tree_txt.insert(INSERT,_expr has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        self.string(Mytokens)
        if(inToken[1] == ")"):
            self.tree_txt.insert(
                INSERT, "child node (internal): seperator" + "\n")
            self.tree_txt.insert(
                INSERT, "   self.tree_txt.insert(INSERT,_expr has child node (token):"+inToken[1] + "\n")
            self.accept_token(Mytokens)
        else:
            self.tree_txt.insert(
                INSERT, "expect identifier as the first element of the self.tree_txt.insert(INSERT,_expr!\n")
            self.accept_token(Mytokens)
            return

    def parser(self, Mytokens):
        global inToken
        inToken = Mytokens.pop(0)
        if(inToken[1] == "if"):
            self.if_exp(Mytokens)
        elif(inToken[0] == "keyword"):
            self.exp(Mytokens)
        else:
            self.print_expr(Mytokens)
        if(inToken[1] == ";" or inToken[1] == ":"):
            self.tree_txt.insert(
                INSERT, "\nparse tree building success!" + "\n")
            return


if __name__ == '__main__':
    myTkRoot = Tk()
    my_gui = LexGUI(myTkRoot)
    myTkRoot.mainloop()
