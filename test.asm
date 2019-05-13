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
13          001B                               LDA               =W'5'             
14          001E             CLOOP             +JSUB             RDREC             
15          0022                               LDA               LENGTH            
16          0025                               COMP              #0                
17          0028                               JEQ               ENDFIL            
18          002B                               +JSUB             WRREC             
19          002F                               J                 CLOOP             
20          0032             ENDFIL            LDA               EOF               
21          0035                               STA               BUFFER            
22          0038                               LDA               #3                
23          003B                               STA               LENGTH            
24          003E                               +JSUB             WRREC             
25          0042                               J                 @RETADR           
26          0045             EOF               BYTE              C'EOF'            
27          0048             SOSO              EQU               FIRST+5           
28          0048             STR               BYTE              C'test STRING'    
29          0053             RETADR            RESW              1                 
30          0056             LENGTH            RESW              1                 
31          0059             BUFFER            RESB              1                 
32                         .
33                         .SUBROUTINE TO READ INTO BUFFER
34          005A             RDREC             CLEAR             X                 
35          005C                               CLEAR             A                 
36          005E                               CLEAR             S                 
37          0060                               +LDT              #4096             
38          0064             RLOOP             TD                INPUT             
39          0067                               JEQ               RLOOP             
40          006A                               TD                INPUT             
41          006D                               COMPR             A,S               
42          006F                               JEQ               EXIT              
43          0072                               STCH              BUFFER,X          
44          0075                               TIXR              T                 
45          0077                               JLT               RLOOP             
46          007A             EXIT              STX               LENGTH            
47          007D                               RSUB                                
48          0080             INPUT             BYTE              X'F1'             
49          0081             WRREC             CLEAR             X                 
50          0083                               LDT               LENGTH            
51          0086             WLOOP             TD                OUTPUT            
52          0089                               JEQ               WLOOP             
53          008C                               LDCH              BUFFER,X          
54          008F                               WD                OUTPUT            
55          0092                               TIXR              T                 
56          0094                               JLT               WLOOP             
57          0097                               RSUB                                
58          009A             OUTPUT            BYTE              X'05'             
59          009B                               END               FIRST             
60          009B                               WORD              5                 
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          INPUT               0080
          WRREC               0081
          RLOOP               0064
          RDREC               005A
          BUFFER              0059
          LENGTH              0056
          L1                  0000
          FIRST               0006
          CLOOP               001E
          OUTPUT              009A
          L2                  0003
          EXIT                007A
          DIFF                0003
          ENDFIL              0032
          EOF                 0045
          RETADR              0053
          SOSO                000B
          WLOOP               0086
          STR                 0048
                         **************************************************
                         ********** S t a r t  o f  P a s s  II ***********
LC        Code      Label     Opcode    Operand     Flags

0000                COPY      START     0000        n=0 i=0 x=0   b=0 p=0 e=0

0000      000064    L1        WORD      100         n=0 i=0 x=0   b=0 p=0 e=0

0003      0000C8    L2        WORD      200         n=0 i=0 x=0   b=0 p=0 e=0

0006                DIFF      EQU       L2-L1       n=0 i=0 x=0   b=0 p=0 e=0

0006      17204A    FIRST     STL       RETADR      n=1 i=1 x=0   b=0 p=1 e=0

0009      03204A              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

000C      012047              LDA       #LENGTH     n=0 i=1 x=0   b=0 p=1 e=0

000F      022044              LDA       @LENGTH     n=1 i=0 x=0   b=0 p=1 e=0

0012      030003              LDA       DIFF        n=1 i=1 x=0   b=0 p=0 e=0

0015      010003              LDA       #DIFF       n=0 i=1 x=0   b=0 p=0 e=0

0018      020003              LDA       @DIFF       n=1 i=0 x=0   b=0 p=0 e=0

001B      03207D              LDA       =W'5'       n=1 i=1 x=0   b=0 p=1 e=0

001E      4B10005A  CLOOP     +JSUB     RDREC       n=1 i=1 x=0   b=0 p=0 e=1

0022      032031              LDA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

0025      290000              COMP      #0          n=0 i=1 x=0   b=0 p=0 e=0

0028      332007              JEQ       ENDFIL      n=1 i=1 x=0   b=0 p=1 e=0

002B      4B100081            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

002F      3F2FEC              J         CLOOP       n=1 i=1 x=0   b=0 p=1 e=0

0032      032010    ENDFIL    LDA       EOF         n=1 i=1 x=0   b=0 p=1 e=0

0035      0F2021              STA       BUFFER      n=1 i=1 x=0   b=0 p=1 e=0

0038      010003              LDA       #3          n=0 i=1 x=0   b=0 p=0 e=0

003B      0F2018              STA       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

003E      4B100081            +JSUB     WRREC       n=1 i=1 x=0   b=0 p=0 e=1

0042      3E200E              J         @RETADR     n=1 i=0 x=0   b=0 p=1 e=0

0045      454F46    EOF       BYTE      C'EOF'      n=0 i=0 x=0   b=0 p=0 e=0

0048                SOSO      EQU       FIRST+5     n=0 i=0 x=0   b=0 p=0 e=0

0048      7465737420535452494E47STR       BYTE      C'test STRING'n=0 i=0 x=0   b=0 p=0 e=0

0053                RETADR    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0056                LENGTH    RESW      1           n=0 i=0 x=0   b=0 p=0 e=0

0059                BUFFER    RESB      1           n=0 i=0 x=0   b=0 p=0 e=0

005A      B410      RDREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

005C      B400                CLEAR     A           n=0 i=0 x=0   b=0 p=0 e=0

005E      B440                CLEAR     S           n=0 i=0 x=0   b=0 p=0 e=0

0060      75101000            +LDT      #4096       n=0 i=1 x=0   b=0 p=0 e=1

0064      E32019    RLOOP     TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

0067      332FFA              JEQ       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

006A      E32013              TD        INPUT       n=1 i=1 x=0   b=0 p=1 e=0

006D      A004                COMPR     A,S         n=0 i=0 x=0   b=0 p=0 e=0

006F      332008              JEQ       EXIT        n=1 i=1 x=0   b=0 p=1 e=0

0072      57AFE4              STCH      BUFFER,X    n=1 i=1 x=1   b=0 p=1 e=0

0075      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

0077      3B2FEA              JLT       RLOOP       n=1 i=1 x=0   b=0 p=1 e=0

007A      132FD9    EXIT      STX       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

007D      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

0080      F1        INPUT     BYTE      X'F1'       n=0 i=0 x=0   b=0 p=0 e=0

0081      B410      WRREC     CLEAR     X           n=0 i=0 x=0   b=0 p=0 e=0

0083      772FD0              LDT       LENGTH      n=1 i=1 x=0   b=0 p=1 e=0

0086      E32011    WLOOP     TD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

0089      332FFA              JEQ       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

008C      53AFCA              LDCH      BUFFER,X    n=1 i=1 x=1   b=0 p=1 e=0

008F      DF2008              WD        OUTPUT      n=1 i=1 x=0   b=0 p=1 e=0

0092      B850                TIXR      T           n=0 i=0 x=0   b=0 p=0 e=0

0094      3B2FEF              JLT       WLOOP       n=1 i=1 x=0   b=0 p=1 e=0

0097      4F0000              RSUB                  n=1 i=1 x=0   b=0 p=0 e=0

009A      05        OUTPUT    BYTE      X'05'       n=0 i=0 x=0   b=0 p=0 e=0

009B                          END       FIRST       n=0 i=0 x=0   b=0 p=0 e=0

009B      000005              WORD      5           n=0 i=0 x=0   b=0 p=0 e=0

                         ***** S U C C E S S F U L L Y  A S S E M B L E D *****
