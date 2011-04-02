Problem:    modelo
Rows:       16
Columns:    12
Non-zeros:  36
Status:     OPTIMAL
Objective:  z = 6460 (MINimum)

   No.   Row name   St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 z            B           6460                             
     2 normal1      NU           200                         200            -6 
     3 normal2      NU           200                         200            -6 
     4 normal3      NU           200                         200            -8 
     5 extra3       NU            40                          40            -6 
     6 sub1         B            200                         200 
     7 sub2         B             10                          50 
     8 sub3         NU            50                          50            -2 
     9 esto1        NU           250                         250           -10 
    10 esto2        B            160                         200 
    11 esto3        NS           200           200             =             2 
    12 atras1       B              0                         150 
    13 atras2       B              0                         300 
    14 demanda1     NS           150           150             =            10 
    15 demanda2     NS           300           300             =            10 
    16 demanda3     NS           700           700             =            12 

   No. Column name  St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 x1n          B            200             0               
     2 x2n          B            200             0               
     3 x3n          B            200             0               
     4 x3e          B             40             0               
     5 x1s          B            200             0               
     6 x2s          B             10             0               
     7 x3s          B             50             0               
     8 x1z          B            250             0               
     9 x2z          B            160             0               
    10 x3z          B            200             0               
    11 x1a          NL             0             0                          20 
    12 x2a          NL             0             0                          20 

Karush-Kuhn-Tucker optimality conditions:

KKT.PE: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.DE: max.abs.err = 0.00e+00 on column 0
        max.rel.err = 0.00e+00 on column 0
        High quality

KKT.DB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
