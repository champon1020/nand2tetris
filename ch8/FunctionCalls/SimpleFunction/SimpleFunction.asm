@256
D=A
@SP
M=D
(SimpleFunction.test)
D=0
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
M=D
@SP
M=M+1
@LCL
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
A=M
A=A+1
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=!M
@SP
A=M
M=D
@SP
M=M+1
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
@SP
A=M
M=D
@SP
M=M+1
@ARG
A=M
A=A+1
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@R11
M=D
@5
D=A
@R11
A=M-D
D=M
@R12
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R11
AM=M-1
D=M
@THAT
M=D
@R11
AM=M-1
D=M
@THIS
M=D
@R11
AM=M-1
D=M
@ARG
M=D
@R11
AM=M-1
D=M
@LCL
M=D
@R12
A=M
0;JMP
(END)
@END
0;JMP
