line no.    Address          Label          Mnemonic          Operands          Comment
1                         .234567890123456789
2           1000             LAB2C             START             1000              
3           1000                               LDA               ALPHA             
4           1003                               LDB               #10               
5           1006                               LDX               #0                
6           1009                               ADDR              A,B               
7           100B                               STA               SAVEW,X           
8           100E                               LDX               #1                
9           1011                               STA               SAVEW,X           
10                         .FORMAT 4
11          1014                               SUB               #12               
12          1018                               LDX               #0                
13          101B                               LDCH              HEXCHAR           
14          101E                               STA               INPUT             
15          1021             LOOP              LDCH              STRING,X          
16          1024                               COMP              INPUT             
17          1027                               JEQ               FOUND             
18          102A                               STCH              OUTPUT,X          
19          102D                               TIX               #5                
20          1030                               JLT               LOOP              
21          1033             FOUND             J                 OUT               
22          1036             ALPHA             WORD              2                 
23          1039             SAVEW             RESW              2                 
24          103F             HEXCHAR           BYTE              X'61'             
25          1040             INPUT             RESB              1                 
26          1041             STRING            BYTE              C'STRING'         
27          1047             OUTPUT            RESB              5                 
28          104C             OUT               END                                 
                         *** ERROR: this statement can't have a label ***
                          *** I N C O M P L E T E    A S S E M B L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          OUTPUT              1047
          STRING              1041
          HEXCHAR             103F
          INPUT               1040
          SAVEW               1039
          ALPHA               1036
          FOUND               1033
          LOOP                1021
