line no.    Address          Label          Mnemonic          Operands          Comment
1                         .2345678901234567890
2           0000             COPY              START             0000              
3           0000             FIRST             STL               RETADR            
4           0003                               LDB               #LENGTH           
5           0006                               BASE              LENGTH            
6           0006             L1                WORD              100               
7           0009             L2                WORD              50                
8           000C             CLOOP             +JSUB             RDREC             
9           0010                               LDA               LENGTH            
10          0013                               COMP              #0                
11          0016                               JEQ               ENDFIL            
12          0019                               +JSUB             WRREC             
13          001D                               J                 CLOOP             
14          0020                               ORG               L2-L1             
15          0003             ENDFIL            LDA               EOF               
16          0006                               STA               BUFFER            
17          0009                               LDA               #3                
18          000C                               STA               LENGTH            
19          000F                               +JSUB             WRREC             
20          0013                               J                 @RETADR           
21          0016             EOF               BYTE              C'EOF'            
22          0019             RETADR            RESW              1                 
23          001C             LENGTH            RESW              1                 
24          001F             BUFFER            RESB              4096              
25                         .
26                         .SUBROUTINE TO READ INTO BUFFER
27          101F             RDREC             CLEAR             X                 
28          1021                               CLEAR             A                 
29          1023                               CLEAR             S                 
30          1025                               +LDT              #4096             
31          1029             RLOOP             TD                INPUT             
32          102C                               JEQ               RLOOP             
33          102F                               TD                INPUT             
34          1032                               COMPR             A,S               
35          1034                               JEQ               EXIT              
36          1037                               STCH              BUFFER,X          
37          103A                               TIXR              T                 
38          103C                               JLT               RLOOP             
39          103F             EXIT              STX               LENGTH            
40          1042                               RSUB                                
41          1045             INPUT             BYTE              X'F1'             
42          1046             WRREC             CLEAR             X                 
43          1048                               LDT               LENGTH            
44          104B             WLOOP             TD                OUTPUT            
45          104E                               JEQ               WLOOP             
46          1051                               LDCH              BUFFER,X          
47          1054                               WD                OUTPUT            
48          1057                               TIXR              T                 
49          1059                               JLT               WLOOP             
50          105C                               RSUB                                
51          105F             OUTPUT            BYTE              X'05'             
52          1060             OP                EQU               L2-L1             
53          1060                               END               FIRST             
                         *** P A S S   1   E N D E D   S U C C E S S F U L L Y ***

           S Y M B O L  T A B L E
          ************************
          NAME               VALUE 
          ************************
          OP                  0003
          WLOOP               104B
          INPUT               1045
          EXIT                103F
          WRREC               1046
          RLOOP               1029
          FIRST               0000
          L1                  0006
          CLOOP               000C
          OUTPUT              105F
          L2                  0009
          BUFFER              001F
          ENDFIL              0003
          RDREC               101F
          EOF                 0016
          RETADR              0019
          LENGTH              001C
