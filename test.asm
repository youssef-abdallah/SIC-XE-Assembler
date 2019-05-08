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
16          0026                               +JSUB             WRRECC            
17          002A                               J                 @RETADR           
18          002D             EOF               BYTE              C'EOF'            
19          0030             RETADR            RESW              1                 
20          0033             LENGTH            RESW              1                 
21          0036             BUFFER            RESB              4096              
22                         .
23                         .SUBROUTINE TO READ INTO BUFFER
24          1036             RDREC             CLEAR             X                 
25          1038                               CLEAR             A                 
26          103A                               CLEAR             S                 
27          103C                               +LDT              #4096             
28          1040             RLOOP             TD                INPUT             
29          1043                               JEQ               RLOOP             
30          1046                               TD                INPUT             
31          1049                               COMPR             A,S               
32          104B                               JEQ               EXIT              
33          104E                               STCH              BUFFER,X          
34          1051                               TIXR              T                 
35          1053                               JLT               RLOOP             
36          1056             EXIT              STX               LENGTH            
37          1059                               RSUB                                
38          105C             INPUT             BYTE              X'F1'             
39          105D             WRREC             CLEAR             X                 
40          105F                               LDT               LENGTH            
41          1062             WLOOP             TD                OUTPUT            
42          1065                               JEQ               WLOOP             
43          1068                               LDCH              BUFFER,X          
44          106B                               WD                OUTPUT            
45          106E                               TIXR              T                 
46          1070                               JLT               WLOOP             
47          1073                               RSUB                                
48          1076             OUTPUT            BYTE              X'05'             
49          1077                               END               FIRST             
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          OUTPUT              1076
          WLOOP               1062
          INPUT               105C
          FIRST               0000
          CLOOP               0006
          ENDFIL              001A
          RDREC               1036
          EOF                 002D
          RETADR              0030
          LENGTH              0033
          BUFFER              0036
          WRREC               105D
          RLOOP               1040
          EXIT                1056
                         **************************************************
                         ********** S t a r t  o f  P a s s  II ***********
LC        Code      Label     Opcode    Operand     Flags

0000                COPY      0000      START       n=0 i=0 x=0   b=0 p=0 e=0

0000      17202D    FIRST     RETADR    STL         n=1 i=1 x=0   b=0 p=1 e=0

0003      69202D              #LENGTH   LDB         n=0 i=1 x=0   b=0 p=1 e=0

0006                          LENGTH    BASE        n=0 i=0 x=0   b=0 p=0 e=0

0006      4B101036  CLOOP     RDREC     +JSUB       n=1 i=1 x=0   b=0 p=0 e=1

000A      032026              LENGTH    LDA         n=1 i=1 x=0   b=0 p=1 e=0

000D      290000              #0        COMP        n=0 i=1 x=0   b=0 p=0 e=0

0010      332007              ENDFIL    JEQ         n=1 i=1 x=0   b=0 p=1 e=0

0013      4B10105D            WRREC     +JSUB       n=1 i=1 x=0   b=0 p=0 e=1

0017      3F2FEC              CLOOP     J           n=1 i=1 x=0   b=0 p=1 e=0

001A      032010    ENDFIL    EOF       LDA         n=1 i=1 x=0   b=0 p=1 e=0

001D      0F2016              BUFFER    STA         n=1 i=1 x=0   b=0 p=1 e=0

0020      010003              #3        LDA         n=0 i=1 x=0   b=0 p=0 e=0

0023      0F200D              LENGTH    STA         n=1 i=1 x=0   b=0 p=1 e=0

0026      4B100000            WRRECC    +JSUB       n=1 i=1 x=0   b=0 p=0 e=1

002A      3E2003              @RETADR   J           n=1 i=0 x=0   b=0 p=1 e=0

002D      454F46    EOF       C'EOF'    BYTE        n=0 i=0 x=0   b=0 p=0 e=0

0030                RETADR    1         RESW        n=0 i=0 x=0   b=0 p=0 e=0

0033                LENGTH    1         RESW        n=0 i=0 x=0   b=0 p=0 e=0

0036                BUFFER    4096      RESB        n=0 i=0 x=0   b=0 p=0 e=0

1036      B410      RDREC     X         CLEAR       n=0 i=0 x=0   b=0 p=0 e=0

1038      B400                A         CLEAR       n=0 i=0 x=0   b=0 p=0 e=0

103A      B440                S         CLEAR       n=0 i=0 x=0   b=0 p=0 e=0

103C      75101000            #4096     +LDT        n=0 i=1 x=0   b=0 p=0 e=1

1040      E32019    RLOOP     INPUT     TD          n=1 i=1 x=0   b=0 p=1 e=0

1043      332FFA              RLOOP     JEQ         n=1 i=1 x=0   b=0 p=1 e=0

1046      E32013              INPUT     TD          n=1 i=1 x=0   b=0 p=1 e=0

1049      A004                A,S       COMPR       n=0 i=0 x=0   b=0 p=0 e=0

104B      332008              EXIT      JEQ         n=1 i=1 x=0   b=0 p=1 e=0

104E      57C003              BUFFER,X  STCH        n=1 i=1 x=1   b=1 p=0 e=0

1051      B850                T         TIXR        n=0 i=0 x=0   b=0 p=0 e=0

1053      3B2FEA              RLOOP     JLT         n=1 i=1 x=0   b=0 p=1 e=0

1056      134000    EXIT      LENGTH    STX         n=1 i=1 x=0   b=1 p=0 e=0

1059      4F0000                        RSUB        n=1 i=1 x=0   b=0 p=0 e=0

105C      F1        INPUT     X'F1'     BYTE        n=0 i=0 x=0   b=0 p=0 e=0

105D      B410      WRREC     X         CLEAR       n=0 i=0 x=0   b=0 p=0 e=0

105F      774000              LENGTH    LDT         n=1 i=1 x=0   b=1 p=0 e=0

1062      E32011    WLOOP     OUTPUT    TD          n=1 i=1 x=0   b=0 p=1 e=0

1065      332FFA              WLOOP     JEQ         n=1 i=1 x=0   b=0 p=1 e=0

1068      53C003              BUFFER,X  LDCH        n=1 i=1 x=1   b=1 p=0 e=0

106B      DF2008              OUTPUT    WD          n=1 i=1 x=0   b=0 p=1 e=0

106E      B850                T         TIXR        n=0 i=0 x=0   b=0 p=0 e=0

1070      3B2FEF              WLOOP     JLT         n=1 i=1 x=0   b=0 p=1 e=0

1073      4F0000                        RSUB        n=1 i=1 x=0   b=0 p=0 e=0

1076      05        OUTPUT    X'05'     BYTE        n=0 i=0 x=0   b=0 p=0 e=0

1077                          FIRST     END         n=0 i=0 x=0   b=0 p=0 e=0

                         ***** S U C C E S S F U L L Y  A S S E M B L E D ****
