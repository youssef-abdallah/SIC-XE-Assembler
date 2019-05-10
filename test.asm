line no.    Address          Label          Mnemonic          Operands          Comment
1                         .2345678901234567890
2           0000             COPY              START             0000              
3           0000             FIRST             STL               RETADR            
4           0003                               LDB               #LENGTH           
5           0006                               BASE              LENGTH            
6           0006             CLOOP             +JSUB             RDREC             
7           000A                               LDA               LENGTH            
8           000D                               COMP              #0                
9           0010                               JEQ               ENDFIL            
10          0013                               +JSUB             WRREC             
11          0017                               J                 CLOOP             
12          001A             ENDFIL            LDA               EOF               
13          001D                               STA               BUFFER            
14          0020                               LDA               #3                
15          0023                               STA               LENGTH            
16          0026                               +JSUB             WRREC             
17          002A                               J                 @RETADR           
18          002D             EOF               BYTE              C'EOF'            
19          0030             SOSO              EQU               FIRST+5           
20          0030             STR               BYTE              C'test STRING'    
21          003B             RETADR            RESW              1                 
22          003E             LENGTH            RESW              1                 
23          0041             BUFFER            RESB              4096              
24                         .
25                         .SUBROUTINE TO READ INTO BUFFER
26          1041             RDREC             CLEAR             X                 
27          1043                               CLEAR             A                 
28          1045                               CLEAR             S                 
29          1047                               +LDT              #4096             
30          104B             RLOOP             TD                INPUT             
31          104E                               JEQ               RLOOP             
32          1051                               TD                INPUT             
33          1054                               COMPR             A,S               
34          1056                               JEQ               EXIT              
35          1059                               STCH              BUFFER,X          
36          105C                               TIXR              T                 
37          105E                               JLT               RLOOP             
38          1061             EXIT              STX               LENGTH            
39          1064                               RSUB                                
40          1067             INPUT             BYTE              X'F1'             
41          1068             WRREC             CLEAR             X                 
42          106A                               LDT               LENGTH            
43          106D             WLOOP             TD                OUTPUT            
44          1070                               JEQ               WLOOP             
45          1073                               LDCH              BUFFER,X          
46          1076                               WD                OUTPUT            
47          1079                               TIXR              T                 
48          107B                               JLT               WLOOP             
49          107E                               RSUB                                
50          1081             OUTPUT            BYTE              X'05'             
51          1082                               END               FIRST             
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          OUTPUT              1081
          INPUT               1067
          EXIT                1061
          WRREC               1068
          RLOOP               104B
          FIRST               0000
          CLOOP               0006
          ENDFIL              001A
          RDREC               1041
          EOF                 002D
          RETADR              003B
          SOSO                0005
          WLOOP               106D
          STR                 0030
          LENGTH              003E
          BUFFER              0041
                         **************************************************
                         ********** S t a r t  o f  P a s s  II ***********
LC        Code      Label     Opcode    Operand     Flags

0000                COPY      START     0000        n=0 i=0 x=0   b=0 p=0 e=0

0000      172038    FIRST     STL       RETADR      n=1 i=1 x=0   b=0 p=1 e=0

0003      692038              LDB       #LENGTH     n=0 i=1 x=0   b=0 p=1 e=0

0006                          BASE      LENGTH      n=0 i=0 x=0   b=0 p=0 e=0

0006      4B101041  CLOOP     +JSUB     RDREC       n=1 i=1 x=0   b=0 p=0 e=1

000A      032031              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

000D      290000              COMP      #0          n=0 i=1 x=0   b=0 p=0 e=0

0010      332007              JEQ       ENDFIL      n=1 i=1 x=0   b=0 p=1 e=0

0013      4B101068            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

0017      3F2FEC              J         CLOOP       n=1 i=1 x=0   b=0 p=1 e=0

001A      032010    ENDFIL    LDA       EOF         n=1 i=1 x=0   b=0 p=1 e=0

001D      0F2021              STA       BUFFER      n=1 i=1 x=0   b=0 p=1 e=0

0020      010003              LDA       #3          n=0 i=1 x=0   b=0 p=0 e=0

0023      0F2018              STA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

0026      4B101068            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

002A      3E200E              J         @RETADR     n=1 i=0 x=0   b=0 p=1 e=0

002D      454F46    EOF       BYTE      C'EOF'      n=0 i=0 x=0   b=0 p=0 e=0

0030                SOSO      EQU       FIRST+5     n=0 i=0 x=0   b=0 p=0 e=0

0030      7465737420535452494E47STR       BYTE      C'test STRING'n=0 i=0 x=0   b=0 p=0 e=0

003B                RETADR    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

003E                LENGTH    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0041                BUFFER    RESB      4096        n=0 i=0 x=0   b=0 p=0 e=0

1041      B410      RDREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

1043      B400                CLEAR     A           n=0 i=0 x=0   b=0 p=0 e=0

1045      B440                CLEAR     S           n=0 i=0 x=0   b=0 p=0 e=0

1047      75101000            +LDT      #4096       n=0 i=1 x=0   b=0 p=0 e=1

104B      E32019    RLOOP     TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

104E      332FFA              JEQ       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1051      E32013              TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

1054      A004                COMPR     A,S         n=0 i=0 x=0   b=0 p=0 e=0

1056      332008              JEQ       EXIT        n=1 i=1 x=0   b=0 p=1 e=0

1059      57C003              STCH      BUFFER,X    n=1 i=1 x=1   b=1 p=0 e=0

105C      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

105E      3B2FEA              JLT       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1061      134000    EXIT      STX       LENGTH      n=1 i=1 x=0   b=1 p=0 e=0

1064      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

1067      F1        INPUT     BYTE      X'F1'       n=0 i=0 x=0   b=0 p=0 e=0

1068      B410      WRREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

106A      774000              LDT       LENGTH      n=1 i=1 x=0   b=1 p=0 e=0

106D      E32011    WLOOP     TD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

1070      332FFA              JEQ       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1073      53C003              LDCH      BUFFER,X    n=1 i=1 x=1   b=1 p=0 e=0

1076      DF2008              WD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

1079      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

107B      3B2FEF              JLT       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

107E      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

1081      05        OUTPUT    BYTE      X'05'       n=0 i=0 x=0   b=0 p=0 e=0

1082                          END       FIRST       n=0 i=0 x=0   b=0 p=0 e=0

                         ***** S U C C E S S F U L L Y  A S S E M B L E D *****
