# Script TCL que gera a simulação da rede


# Inclui o arquivo que define a variável "transmissores", com o número de transmissores para a simulação
# Esse arquivo é gerado dinamicamente pelo Shell Script, que o cria para cada número de transmissores (30, 40, 50, e 60)
source config.tcl


# Número de switches
set numSwitches 4

# Número de máquinas por switch
set maquinasPorSwitch 48

# Velocidade dos links da rede
set velocidadeRede 100Mb

# Delay dos links da rede
set delayRede 10ms

# Número de Receptores
set receptores 10


# Tempo de simulação, em segundos
set tempo 3.0

# Tamanho dos pacotes a serem trasmitidos, em bytes
set packSize 1000

# Intervalo de tempo de envio dos pacotes, em segundos
set interval 0.00003



#--------------------------#


# cria objeto simulador
set ns [new Simulator]

#Abre o arquivo de trace
set file1 [open out-$transmissores.tr w]
$ns trace-all $file1

# abre o arquivo trace do nam
set namtraceFilename out-$transmissores.nam
set nf [open $namtraceFilename w]
$ns namtrace-all $nf

# define a função finish
proc finish {} {
	global ns nf namtraceFilename
	$ns flush-trace
	close $nf
	#exec nam $namtraceFilename &
	exit 0
}



# cria os switches
for {set i 0} {$i < $numSwitches} {incr i} {
	set s($i) [$ns node]
	$s($i) color Red
	$s($i) shape box
}

set j 0
# liga os switches em linha
for {set i 0} {$i < $numSwitches-1} {incr i} {
	set j [expr ($i+1)]
	$ns duplex-link $s($i) $s($j) $velocidadeRede $delayRede DropTail
}


# liga máquinas a cada switch
for {set i 0} {$i < $numSwitches} {incr i} {
	for {set j 0} {$j < $maquinasPorSwitch} {incr j} {
		set x [expr ($i * $maquinasPorSwitch + $j)]
		set n($x) [$ns node]
		$ns duplex-link $s($i) $n($x) $velocidadeRede $delayRede DropTail
	}
	
}


# define que as últimas máquinas inseridas serão receptoras
# Essa decisão foi tomada a fim de facilitar a geração de
# transmissores, bastando randomizar núemros abaixo de um 
# valor fixo (acima do qual só existem receptores)
set j 0
#for {set i $x} {$i > [expr $x - $receptores]} {set i [expr $i - 1]} {
	#set null($j) [new Agent/Null]
	#$ns attach-agent $n($i) $null($j)
	#incr j
#}



# define os transmissores aleatoriamente
set modRandom [expr $maquinasPorSwitch * $numSwitches]
set num [expr { int($modRandom * rand()) }]
set arrTR($num) 1

set i 0

set udp($i) [new Agent/UDP]
$ns attach-agent $n($i) $udp($i)
set cbr($i) [new Application/Traffic/CBR]
$cbr($i) set packetSize_ $packSize
$cbr($i) set interval_ $interval
$cbr($i) attach-agent $udp($i)

while {$i < $transmissores} {
	set num [expr { int($modRandom * rand()) }]
	if { [info exists arrTR($num)] } {
		#puts "$num já está no array"
	} else {
		set arrTR($num) 1
		set udp($i) [new Agent/UDP]
		$ns attach-agent $n($num) $udp($i)
		$n($num) color Yellow
		set cbr($i) [new Application/Traffic/CBR]
		$cbr($i) set packetSize_ $packSize
		$cbr($i) set interval_ $interval
		$cbr($i) attach-agent $udp($i)
		incr i
	}
}

		# a conexão será feita com $null(0..9), logo
		# precisamos assegurar que não haverá um número maior que 9
set i 0 
while {$i < $receptores} { 
	set num [expr { int($modRandom * rand()) }]
	if { [info exists arrTR($num)] } {
		#puts "$num já está no array"
		


	} else {
		set arrTR($num) 1
		set null($i) [new Agent/Null]
		$ns attach-agent $n($num) $null($i)
		$n($num) color Blue
		incr i

	}
}

for {set i 0} {$i < $transmissores} {incr i} {
                set indice [expr { $i % $receptores} ]
		$ns connect $udp($i) $null($indice)
}

for {set i 0} {$i < $transmissores} {incr i} {
	$ns at 0.0 "$cbr($i) start"
	$ns at $tempo "$cbr($i) stop"
}



# chama "finish" após "tempo" segundos de simulação
$ns at $tempo "finish"


$ns run



