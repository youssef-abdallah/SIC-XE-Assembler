line no.    Address          Label          Mnemonic          Operands          Comment
1                         .2345678901234567890
2           0000             COPY              START             0000              
3           0000             L1                WORD              100               
4           0003             L2                WORD              200               
5           0006             DIFF              EQU               L2-L1             
6           0006             FIRST             STL               RETADR            
7           0009                               LDA               LENGTH            
8           000C                               LDA               #LENGTH           
9           000F                               LDA               @LENGTH           
10          0012                               LDA               DIFF              
11          0015                               LDA               #DIFF             
12          0018                               LDA               @DIFF             
13          001B             CLOOP             +JSUB             RDREC             
14          001F                               LDA               LENGTH            
15          0022                               COMP              #0                
16          0025                               JEQ               ENDFIL            
17          0028                               +JSUB             WRREC             
18          002C                               J                 CLOOP             
19          002F             ENDFIL            LDA               EOF               
20          0032                               STA               BUFFER            
21          0035                               LDA               #3                
22          0038                               STA               LENGTH            
23          003B                               +JSUB             WRREC             
24          003F                               J                 @RETADR           
25          0042             EOF               BYTE              C'EOF'            
26          0045             SOSO              EQU               FIRST+5           
27          0045             STR               BYTE              C'test STRING'    
28          0050             RETADR            RESW              1                 
29          0053             LENGTH            RESW              1                 
30          0056             BUFFER            RESB              4096              
31                         .
32                         .SUBROUTINE TO READ INTO BUFFER
33          1056             RDREC             CLEAR             X                 
34          1058                               CLEAR             A                 
35          105A                               CLEAR             S                 
36          105C                               +LDT              #4096             
37          1060             RLOOP             TD                INPUT             
38          1063                               JEQ               RLOOP             
39          1066                               TD                INPUT             
40          1069                               COMPR             A,S               
41          106B                               JEQ               EXIT              
42          106E                               STCH              BUFFER,X          
43          1071                               TIXR              T                 
44          1073                               JLT               RLOOP             
45          1076             EXIT              STX               LENGTH            
46          1079                               RSUB                                
47          107C             INPUT             BYTE              X'F1'             
48          107D             WRREC             CLEAR             X                 
49          107F                               LDT               LENGTH            
50          1082             WLOOP             TD                OUTPUT            
51          1085                               JEQ               WLOOP             
52          1088                               LDCH              BUFFER,X          
53          108B                               WD                OUTPUT            
54          108E                               TIXR              T                 
55          1090                               JLT               WLOOP             
56          1093                               RSUB                                
57          1096             OUTPUT            BYTE              X'05'             
58          1097                               END               FIRST             
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          INPUT               107C
          WRREC               107D
          RLOOP               1060
          RDREC               1056
          BUFFER              0056
          LENGTH              0053
          L1                  0000
          FIRST               0006
          CLOOP               001B
          OUTPUT              1096
          L2                  0003
          EXIT                1076
          DIFF                0003
          ENDFIL              002F
          EOF                 0042
          RETADR              0050
          SOSO                000B
          WLOOP               1082
          STR                 0045
                         **************************************************
                         ********** S t a r t  o f  P a s s  II ***********
LC        Code      Label     Opcode    Operand     Flags

0000                COPY      START     0000        n=0 i=0 x=0   b=0 p=0 e=0

0000      000064    L1        WORD      100         n=0 i=0 x=0   b=0 p=0 e=0

0003      0000C8    L2        WORD      200         n=0 i=0 x=0   b=0 p=0 e=0

0006                DIFF      EQU       L2-L1       n=0 i=0 x=0   b=0 p=0 e=0

0006      172047    FIRST     STL       RETADR      n=1 i=1 x=0   b=0 p=1 e=0

0009      032047              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

000C      012044              LDA       #LENGTH     n=0 i=1 x=0   b=0 p=1 e=0

000F      022041              LDA       @LENGTH     n=1 i=0 x=0   b=0 p=1 e=0

0012      030003              LDA       DIFF        n=1 i=1 x=0   b=0 p=0 e=0

0015      010003              LDA       #DIFF       n=0 i=1 x=0   b=0 p=0 e=0

0018      020003              LDA       @DIFF       n=1 i=0 x=0   b=0 p=0 e=0

001B      4B101056  CLOOP     +JSUB     RDREC       n=1 i=1 x=0   b=0 p=0 e=1

001F      032031              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

0022      290000              COMP      #0          n=0 i=1 x=0   b=0 p=0 e=0

0025      332007              JEQ       ENDFIL      n=1 i=1 x=0   b=0 p=1 e=0

0028      4B10107D            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

002C      3F2FEC              J         CLOOP       n=1 i=1 x=0   b=0 p=1 e=0

002F      032010    ENDFIL    LDA       EOF         n=1 i=1 x=0   b=0 p=1 e=0

0032      0F2021              STA       BUFFER      n=1 i=1 x=0   b=0 p=1 e=0

0035      010003              LDA       #3          n=0 i=1 x=0   b=0 p=0 e=0

0038      0F2018              STA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

003B      4B10107D            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

003F      3E200E              J         @RETADR     n=1 i=0 x=0   b=0 p=1 e=0

0042      454F46    EOF       BYTE      C'EOF'      n=0 i=0 x=0   b=0 p=0 e=0

0045                SOSO      EQU       FIRST+5     n=0 i=0 x=0   b=0 p=0 e=0

0045      7465737420535452494E47STR       BYTE      C'test STRING'n=0 i=0 x=0   b=0 p=0 e=0

0050                RETADR    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0053                LENGTH    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0056                BUFFER    RESB      4096        n=0 i=0 x=0   b=0 p=0 e=0

1056      B410      RDREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

1058      B400                CLEAR     A           n=0 i=0 x=0   b=0 p=0 e=0

105A      B440                CLEAR     S           n=0 i=0 x=0   b=0 p=0 e=0

105C      75101000            +LDT      #4096       n=0 i=1 x=0   b=0 p=0 e=1

1060      E32019    RLOOP     TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

1063      332FFA              JEQ       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1066      E32013              TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

1069      A004                COMPR     A,S         n=0 i=0 x=0   b=0 p=0 e=0

106B      332008              JEQ       EXIT        n=1 i=1 x=0   b=0 p=1 e=0

106E                          STCH      BUFFER,X    ***Error: Wrong operand (Addressing Problem)!***

1071      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

1073      3B2FEA              JLT       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1076                EXIT      STX       LENGTH      ***Error: Wrong operand (Addressing Problem)!***

1079      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

107C      F1        INPUT     BYTE      X'F1'       n=0 i=0 x=0   b=0 p=0 e=0

107D      B410      WRREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

107F                          LDT       LENGTH      ***Error: Wrong operand (Addressing Problem)!***

1082      E32011    WLOOP     TD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

1085      332FFA              JEQ       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1088                          LDCH      BUFFER,X    ***Error: Wrong operand (Addressing Problem)!***

108B      DF2008              WD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

108E      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

1090      3B2FEF              JLT       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

1093      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

1096      05        OUTPUT    BYTE      X'05'       n=0 i=0 x=0   b=0 p=0 e=0

1097                          END       FIRST       n=0 i=0 x=0   b=0 p=0 e=0

                         ***** U N S U C C E S S F U L L   A S S E M B L Y *****
