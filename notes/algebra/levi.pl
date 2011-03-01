#!/usr/bin/perl

$e{111} = 0  ; $e{112} = 0  ; $e{113} = 0 ; 
$e{121} = 0  ; $e{122} = 0  ; $e{123} = 1 ; 
$e{131} = 0  ; $e{132} = -1 ; $e{133} = 0 ;

$e{211} = 0  ; $e{212} = 0  ; $e{213} = -1 ;
$e{221} = 0  ; $e{222} = 0  ; $e{223} = 0 ;
$e{231} = 1  ; $e{232} = 0  ; $e{233} = 0 ;

$e{311} = 0  ; $e{312} = 1  ; $e{313} = 0 ;
$e{321} = -1 ; $e{322} = 0  ; $e{323} = 0 ;
$e{331} = 0  ; $e{332} = 0  ; $e{333} = 0 ;

$d{11} = 1 ; $d{12} = 0 ; $d{13} = 0 ; 
$d{21} = 0 ; $d{22} = 1 ; $d{23} = 0 ; 
$d{31} = 0 ; $d{32} = 0 ; $d{33} = 1 ; 

# prove: \sum_k e_{ijk} e_{klm} 
#   = \delta_{il}\delta_{jm} - \delta_{jl}\delta_{im}
#print "$e{123} $e{113} $e{321}\n" ;

for ( my $i = 1 ; $i <= 3 ; $i++ ) {
 for ( my $j = 1 ; $j <= 3 ; $j++ ) {
  for ( my $l = 1 ; $l <= 3 ; $l++ ) {
   for ( my $m = 1 ; $m <= 3 ; $m++ ) {
    my $lhs = 0 ;
    my $rhs = $d{"${i}${l}"} * $d{"${j}${m}"} 
            - $d{"${j}${l}"} * $d{"${i}${m}"} ;

    for ( my $k = 1 ; $k <= 3 ; $k++ ) {
     $lhs += $e{"${i}${j}${k}"} * $e{"${k}${l}${m}"} ;
    }

    if ( $rhs != $lhs ) {
     print 'ERROR: \\sum_{k=1}^{3} \\epsilon_{' . 
           "${i}${j}k" . 
           '} \\epsilon_{' . 
           "k${l}${m}} = $lhs\n" ;

     print 'ERROR: \\delta_{' . 
           "${i}${l}}" .  '\\delta_{' . 
           "${j}${m}" .  '} - \\delta_{' . 
           "${j}${l}" . '}\\delta_{' . 
           "${i}${m}} = $rhs\n\n" ;
     } else {
      print "$lhs &= " . 
            '\\sum_{k=1}^{3} \\epsilon_{' . 
            "${i}${j}k" . '} \\epsilon_{' . 
            "k${l}${m}} = " . '\\delta_{' . 
            "${i}${l}}" . '\\delta_{' . "${j}${m}" . 
            '} - \\delta_{' . "${j}${l}" . 
            '}\\delta_{' . "${i}${m}}" . 
            ' \\\\' . " \n" ;
} } } } }
